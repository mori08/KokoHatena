#include "EventPlayer.hpp"
#include "EventObject/TextureEventObject/TextureEventObject.hpp"
#include "../../../../../MyLibrary/MyLibrary.hpp"

namespace Kokoha
{
	EventPlayer::EventPlayer(const String& eventFileName, const Size& drawSize)
		: m_render(drawSize)
		, m_eventToml(eventFileName)
	{
		setEventMap();
		setGenerateObjectMap();

		// TODO イベント初期化処理を走らせる
		m_now = m_eventToml[U"init"].tableArrayView().begin();
		m_end = m_eventToml[U"init"].tableArrayView().end();

		while (m_now != m_end)
		{
			m_eventMap[(*m_now)[U"event"].getString()](*m_now);
			++m_now;
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
		while (!m_waitingObject.empty() && !m_waitingObject.front()->wait())
		{
			m_waitingObject.pop_front();
		}

		// イベントの進行
		if (m_now != m_end && m_waitingObject.empty())
		{
			m_eventMap[(*m_now)[U"event"].getString()](*m_now);
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

	void EventPlayer::setEventMap()
	{
		// オブジェクトの生成
		m_eventMap[U"object"] = [this](const TOMLValue& object)
		{
			const String type = object[U"type"].getString();
			const String name = object[U"name"].getString();
			const TOMLValue param = object[U"param"];

			if (!m_generateObjectMap.count(type))
			{
				throw Error(U"EventPlayer: object: 存在しないtypeが指定されている");
			}

			if (m_objectList.count(name))
			{
				throw Error(U"EventPlayer: object: 既に存在するnameが指定されている");
			}

			m_objectList[name] = m_generateObjectMap[type](param);
		};
	}

	void EventPlayer::setGenerateObjectMap()
	{
		m_generateObjectMap[U"texture"] = [](const TOMLValue& param)
		{
			return std::make_shared<TextureEventObject>(param);
		};
	}
}