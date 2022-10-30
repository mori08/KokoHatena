#pragma once
#include"../Board.hpp"

namespace Kokoha
{
	class AccessBoard : public Board
	{
	public:

		AccessBoard();

	private:

		void receiveRequest(const String& requestText) override;

		void inputInBoard() override;

		void updateInBoard(BoardRequest& request) override;

		void drawInBoard() const override;

	};
}