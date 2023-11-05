﻿#pragma once

#include "EventObject/EventObject.hpp"
#include "../../BoardConst.hpp"
#include "../../../../RecordSet/RecordSet.hpp"

namespace Kokoha
{
	/// <summary>
	/// オブジェクトとイベントの管理と再生
	/// </summary>
	class EventPlayer
	{
	private:

		// EventObjectのshared_ptr
		using ObjectPtr = std::shared_ptr<EventObject>;

	private:

		// 描画範囲
		const MSRenderTexture m_render;

		// 読込中のイベント
		TOMLTableArrayIterator m_now;

		// 読込中のイベントのendのイテレータ
		TOMLTableArrayIterator m_end;

		// イベントのTOMLファイル
		const TOMLReader m_eventToml;

		// 文字列からオブジェクトの作成への紐づけ
		std::unordered_map<String, std::function<ObjectPtr(const TOMLValue&)>> m_generateObjectMap;

		// オブジェクトのリスト
		std::map<String, ObjectPtr> m_objectList;

		// 待ち状態のオブジェクト
		std::list<ObjectPtr> m_waitingObjectList;

		// 別イベントに遷移する条件のフラグのリスト
		std::unordered_map<String, bool> m_jumpFlagMap;

		// 待機中のリクエスト
		Optional<String> m_waitingRequest;

		// 待ち時間(s)
		double m_waitingSecond;

	public:

		/// <param name="eventFileName"> イベントのファイル名 </param>
		/// <param name="drawSize"> 描画範囲 </param>
		EventPlayer(const String& eventFileName, const Size& drawSize, const RecordSet& recordSet);

		/// <summary>
		/// 入力
		/// </summary>
		/// <param name="cursorPos"> マウスカーソルの座標 </cursorPos>
		void input(const Vec2& cursorPos);

		/// <summary>
		/// 更新
		/// </summary>
		/// <param name=boardRequest"> ボードへのリクエスト </param>
		void update(BoardRequest& boardRequest);

		/// <summary>
		/// MessageBoardが受け取ったリクエストを受け取る
		/// </summary>
		void receive(const String& requestText);

		/// <summary>
		/// 描画
		/// </summary>
		/// <param name="drawPos"> 描画座標 </param>
		void draw(const Point& drawPos) const;

	private:

		/// <summary>
		/// イベントの実行
		/// </summary>
		/// <param name="nowEvent"> 現在読み込み中のイベント </param>
		/// <param name="boardRequest"> ボード外へのリクエスト </param>
		/// <returns> true のときイベントを進める , jump以外は基本的にtrueを設定 </returns>
		bool playEvent(const TOMLValue& nowEvent, BoardRequest& boardRequest);

		/// <summary>
		/// オブジェクトの生成の関数の登録
		/// </summary>
		void setGenerateObjectMap();

		/// <summary>
		/// Recordと同期するjumpFlagのリストの取得
		/// </summary>
		/// <returns> Recordと同期するjumpFlagのリスト </returns>
		static const Array<String>& recordJumpFlagNameList();

	};
}
