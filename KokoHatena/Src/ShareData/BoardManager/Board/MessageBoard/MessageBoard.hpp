#pragma once
#include"../Board.hpp"
#include"EventPlayer/EventPlayer.hpp"

namespace Kokoha
{
	class MessageBoard : public Board
	{
	private:

		// �b������̃��X�g
		Array<String> m_speakerNameList;

		// �I�𒆂̘b������ (�����I�����Ă��Ȃ��Ƃ��� none)
		Optional<String> m_selectedSpeakerName;

		std::unordered_map<String, EventPlayer> m_eventPlayerMap;

	public:

		MessageBoard();

	private:

		void receiveRequest(const String& requestText) override;

		void inputInBoard() override;

		void updateInBoard(Request& request) override;

		void drawInBoard() const override;

	private:

		/// <summary>
		/// �b�������\������͈�
		/// </summary>
		/// <param name="index"> �ԍ� </param>
		/// <returns> �b�������\������ </returns>
		static Rect getSpeakerNameRect(int32 index);

	};
}