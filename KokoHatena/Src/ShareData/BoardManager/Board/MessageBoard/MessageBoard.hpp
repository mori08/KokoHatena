﻿#pragma once
#include"../Board.hpp"
#include"EventPlayer/EventPlayer.hpp"

namespace Kokoha
{
	class MessageBoard : public Board
	{
	private:

		// 話し相手のリスト
		Array<String> m_speakerNameList;

		// 選択中の話し相手 (何も選択していないときは none)
		Optional<String> m_selectedSpeakerName;

		// 話し相手ごとのEventPlayer
		std::unordered_map<String, EventPlayer> m_eventPlayerMap;

		// 日付
		const int32 m_recordDay;

		// 未読の話者
		std::set<String> m_notReadSpeakerNameSet;

	public:

		MessageBoard(const RecordSet& recordSet);

	private:

		void receiveRequest(const String& requestText) override;

		void inputInBoard() override;

		void updateInBoard(BoardRequest& request) override;

		void drawInBoard() const override;

	private:

		/// <summary>
		/// 話し相手を表示する範囲
		/// </summary>
		/// <param name="index"> 番号 </param>
		/// <returns> 話し相手を表示する </returns>
		static Rect getSpeakerNameRect(int32 index);

	};
}
