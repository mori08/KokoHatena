#pragma once
#include"../Board.hpp"

namespace Kokoha
{
	class MessageBoard : public Board
	{
	public:

		MessageBoard();

	private:

		void receiveRequest(const String& requestText) override;

		BoardRequest inputInBoard() override;

		void updateInBoard() override;

		void drawInBoard() const override;

	};
}