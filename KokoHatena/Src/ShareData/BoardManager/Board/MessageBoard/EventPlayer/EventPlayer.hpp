#pragma once

#include "EventObject/EventObject.hpp"

namespace Kokoha
{
	/// <summary>
	/// オブジェクトとイベントの管理と再生
	/// </summary>
	class EventPlayer
	{
	private:

		// 描画範囲
		const MSRenderTexture m_render;

		// 読込中のイベント
		TOMLTableArrayIterator m_now;

		// 読込中のイベントのendのイテレータ
		TOMLTableArrayIterator m_end;

		// イベントのTOMLファイル
		const TOMLReader m_eventToml;

		// オブジェクトのリスト
		std::map<String, std::unique_ptr<EventObject>> m_objectList;

	public:

		/// <param name="eventFileName"> イベントのファイル名 </param>
		/// <param name="drawSize"> 描画範囲 </param>
		EventPlayer(const String& eventFileName, const Size& drawSize);

		/// <summary>
		/// 更新
		/// </summary>
		void update();

		/// <summary>
		/// 描画
		/// </summary>
		/// <param name="drawPos"> 描画座標 </param>
		void draw(const Point& drawPos) const;

	};
}