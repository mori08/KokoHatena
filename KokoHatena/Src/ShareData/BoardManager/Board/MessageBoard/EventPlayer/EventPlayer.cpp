#include "EventPlayer.hpp"
#include "EventObject/TextureEventObject/TextureEventObject.hpp"
#include "../../../../../MyLibrary/MyLibrary.hpp"

namespace Kokoha
{
	EventPlayer::EventPlayer(const String& eventFileName, const Size& drawSize)
		: m_render(drawSize)
		, m_eventToml(eventFileName)
	{
		setGenerateObjectMap();

		// TODO イベント初期化処理を走らせる
		m_now = m_eventToml[U"init"].tableArrayView().begin();
		m_end = m_eventToml[U"init"].tableArrayView().end();

		// 初期化
		TOMLTableArrayIterator init_now = m_now;
		TOMLTableArrayIterator init_end = m_end;
		while (init_now != init_end)
		{
			BoardRequest tmp; // 仮で作成（初期化でリクエストは送らない）
			playEvent(*init_now, tmp);
			++init_now;
		}
	}

	void EventPlayer::input()
	{
		// オブジェクトの入力
		for (const auto& object : m_objectList)
		{
			object.second->input();
		}
	}

	void EventPlayer::update(BoardRequest& boardRequest)
	{
		// オブジェクトの更新
		for (const auto& object : m_objectList)
		{
			object.second->update();
		}

		// オブジェクトの待ち状態の解消
		while (!m_waitingObjectList.empty() && !m_waitingObjectList.front()->wait())
		{
			m_waitingObjectList.pop_front();
		}
		
		// イベントの進行
		if (m_now != m_end && m_waitingObjectList.empty())
		{
			const String eventName = (*m_now)[U"event"].getString();
			
			playEvent(*m_now, boardRequest);

			++m_now;
		}
	}

	void EventPlayer::draw(const Point& drawPos) const
	{
		// レンダーテクスチャーのクリア
		m_render.clear(MyBlack);

		// レンダーテクスチャーを使って Rect(drawPos, m_render.size()) に描画
		{
			ScopedRenderTarget2D target(m_render);

			// オブジェクトの描画
			for (const auto& object : m_objectList)
			{
				object.second->draw();
			}
		}

		Graphics2D::Flush();
		m_render.resolve();
		m_render.draw(drawPos);
	}

	void EventPlayer::playEvent(const TOMLValue& nowEvent, BoardRequest& boardRequest)
	{
		const String eventName = nowEvent[U"event"].getString(); // イベント名

		// オブジェクトの生成
		if (eventName == U"object")
		{
			const String type = nowEvent[U"type"].getString();
			const String name = nowEvent[U"name"].getString();
			const TOMLValue param = nowEvent[U"param"];

			if (!m_generateObjectMap.count(type))
			{
				throw Error(U"EventPlayer: object: 存在しないtype[" + type + U"]が指定されている");
			}

			if (m_objectList.count(name))
			{
				throw Error(U"EventPlayer: object: 既に存在するname[" + name + U"]が指定されている");
			}

			m_objectList[name] = m_generateObjectMap[type](param);

			return;
		}

		// オブジェクトへの命令
		if (eventName == U"act")
		{
			const String name = nowEvent[U"name"].getString();
			const TOMLValue param = nowEvent[U"param"];
			
			if (!m_objectList.count(name))
			{
				throw Error(U"EventPlayer: act: 存在しないobjectのname[" + name + U"]が指定されている");
			}

			const ObjectPtr objectPtr = m_objectList[name];
			
			objectPtr->receive(param);
			m_waitingObjectList.emplace_back(objectPtr);

			return;
		}

		// 別イベント群への遷移
		if (eventName == U"jamp")
		{
			const String to = nowEvent[U"to"].getString();
			const String flag = nowEvent[U"flag"].getString();

			if (!m_eventToml[to].isTableArray())
			{
				throw Error(U"EventPlayer: jamp: 指定された遷移先to[" + to + U"]は存在しない");
			}

			if (flag != U"" && !m_jampFlagMap.count(flag))
			{
				throw Error(U"EventPlayer: jamp: 指定されたflag[" + flag + U"]は存在しない");
			}

			if (flag == U"" || m_jampFlagMap[flag])
			{
				m_now = m_eventToml[to].tableArrayView().begin();
				m_end = m_eventToml[to].tableArrayView().end();
			}

			return;
		}

		// 他ボードへのリクエスト
		if (eventName == U"board")
		{
			const String role = nowEvent[U"role"].getString();
			const String text = nowEvent[U"text"].getString();
			
			if (!BOARD_ROLE_MAP.count(role))
			{
				throw Error(U"EventPlayer: board: 指定されたBoardRole[" + role + U"]が存在しない");
			}

			boardRequest.toBoard.emplace_back(BOARD_ROLE_MAP.find(role)->second, text);

			return;
		}

		// シーンへのリクエスト
		if (eventName == U"scene")
		{
			const String scene = nowEvent[U"scene"].getString();

			if (!SCENE_NAME_MAP.count(scene))
			{
				throw Error(U"EventPlayer: scene: 指定されたScene[" + scene + U"]は存在しない");
			}

			boardRequest.toScene = SCENE_NAME_MAP.find(scene)->second;

			return;
		}

		throw Error(U"EventPlayer: event[" + eventName + U"]は存在しない");
	}

	void EventPlayer::setGenerateObjectMap()
	{
		m_generateObjectMap[U"texture"] = [](const TOMLValue& param)
		{
			return std::make_shared<TextureEventObject>(param);
		};
	}
}