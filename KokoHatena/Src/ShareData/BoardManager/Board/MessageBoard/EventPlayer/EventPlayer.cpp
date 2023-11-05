#include "EventPlayer.hpp"
#include "EventObject/TextureEventObject/TextureEventObject.hpp"
#include "EventObject/MessageEventObject/MessageEventObject.hpp"
#include "../../../../../MyLibrary/MyLibrary.hpp"
#include "../../../../../Config/Config.hpp"

namespace Kokoha
{
	EventPlayer::EventPlayer(const String& eventFileName, const Size& drawSize, const RecordSet& recordSet)
		: m_render(drawSize)
		, m_eventToml(eventFileName)
		, m_waitingRequest(none)
		, m_waitingSecond(0.0)
	{
		setGenerateObjectMap();

		// イベント初期化処理を走らせる
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

		for (const auto& jumpFlagName : recordJumpFlagNameList())
		{
			const int32 jumpFlagValue = recordSet.getRecord(jumpFlagName);
			m_jumpFlagMap[jumpFlagName] = (jumpFlagValue != 0);
		}
	}

	void EventPlayer::input(const Vec2& cursorPos)
	{
		// オブジェクトの入力
		for (const auto& object : m_objectList)
		{
			object.second->input(cursorPos);
		}
	}

	void EventPlayer::update(BoardRequest& boardRequest)
	{
		// オブジェクトの更新
		for (const auto& object : m_objectList)
		{
			object.second->update();
			object.second->updateJumpFlag(m_jumpFlagMap);
		}

		// オブジェクトの待ち状態の解消
		while (!m_waitingObjectList.empty() && !m_waitingObjectList.front()->wait())
		{
			m_waitingObjectList.pop_front();
		}

		// 待ち時間の更新
		m_waitingSecond -= Scene::DeltaTime();

		// イベントの進行
		bool waiting = !m_waitingObjectList.empty()
			|| m_waitingRequest
			|| m_waitingSecond > 0;
		if (m_now != m_end && !waiting)
		{
			const String eventName = (*m_now)[U"event"].getString();
			
			if (playEvent(*m_now, boardRequest))
			{
				++m_now;
			}
		}
	}

	void EventPlayer::receive(const String& requestText)
	{
		if (m_waitingRequest && m_waitingRequest.value() == requestText)
		{
			m_waitingRequest = none;
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

	bool EventPlayer::playEvent(const TOMLValue& nowEvent, BoardRequest& boardRequest)
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

			return true;
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

			return true;
		}

		// jump時に使用するフラグの設定
		if (eventName == U"flag")
		{
			const String name  = nowEvent[U"name"].getString();
			const bool   value = nowEvent[U"value"].getOr<bool>(true);

			m_jumpFlagMap[name] = value;

			return true;
		}

		// 別イベント群への遷移
		if (eventName == U"jump")
		{
			const String to = nowEvent[U"to"].getString();
			const String flag = nowEvent[U"flag"].getString();

			if (!m_eventToml[to].isTableArray())
			{
				throw Error(U"EventPlayer: jump: 指定された遷移先to[" + to + U"]は存在しない");
			}

			if (flag == U"" || (m_jumpFlagMap.count(flag) && m_jumpFlagMap[flag]))
			{
				m_now = m_eventToml[to].tableArrayView().begin();
				m_end = m_eventToml[to].tableArrayView().end();

				return false;
			}

			return true;
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

			return true;
		}

		// シーンへのリクエスト
		if (eventName == U"scene")
		{
			const String scene = nowEvent[U"scene"].getString();

			if (!SCENE_NAME_MAP.count(scene))
			{
				throw Error(U"EventPlayer: scene: 指定されたScene[" + scene + U"]は存在しない");
			}

			for (const auto& jumpFlagName : recordJumpFlagNameList())
			{
				boardRequest.toRecord[jumpFlagName] = m_jumpFlagMap[jumpFlagName];
			}
			boardRequest.toScene = SCENE_NAME_MAP.find(scene)->second;

			return true;
		}

		// Boardへのリクエストを待機
		if (eventName == U"recieve")
		{
			m_waitingRequest = nowEvent[U"name"].getOpt<String>();

			return true;
		}

		// 待ち時間の設定
		if (eventName == U"wait")
		{
			m_waitingSecond = nowEvent[U"time"].getOr<double>(0.0);

			return true;
		}

		throw Error(U"EventPlayer: event[" + eventName + U"]は存在しない");
	}

	void EventPlayer::setGenerateObjectMap()
	{
		m_generateObjectMap[U"texture"] = [](const TOMLValue& param)
		{
			return std::make_shared<TextureEventObject>(param);
		};
		m_generateObjectMap[U"message"] = [](const TOMLValue& param)
		{
			return std::make_shared<MessageEventObject>(param);
		};
	}

	const Array<String>& EventPlayer::recordJumpFlagNameList()
	{
		static const Array<String> JUMP_FLAG_NAME_LIST = Config::getArray<String>(U"EventPlayer.recordJumpFlagNameList");
		return JUMP_FLAG_NAME_LIST;
	}
}
