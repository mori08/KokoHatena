#include "EventPlayer.hpp"
#include "../../../../../MyLibrary/MyLibrary.hpp"

namespace Kokoha
{
	EventPlayer::EventPlayer(const String& eventFileName, const Size& drawSize)
		: m_render(drawSize)
		, m_eventToml(eventFileName)
	{
		// TODO イベント初期化処理を走らせる
		m_now = m_eventToml[U"example"].tableArrayView().begin();
		m_end = m_eventToml[U"example"].tableArrayView().end();
	}

	void EventPlayer::update()
	{
		if (m_now != m_end)
		{

			++m_now;
		}

		// オブジェクトの更新
		for (const auto& object : m_objectList)
		{
			object.second->update();
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
}