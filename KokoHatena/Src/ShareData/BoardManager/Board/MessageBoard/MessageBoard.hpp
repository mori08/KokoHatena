#pragma once
#include"../Board.hpp"

namespace Kokoha
{
	class MessageBoard : public Board
	{
	private:

		// 話し相手のリスト
		Array<String> m_speakerNameList;

	public:

		MessageBoard();

	private:

		void receiveRequest(const String& requestText) override;

		BoardRequest inputInBoard() override;

		void updateInBoard() override;

		void drawInBoard() const override;

	private:

		static Point getSpeakerNamePos(int32 index);

	};
}