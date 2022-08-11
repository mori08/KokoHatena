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

		BoardRequest inputInBoard() override;

		void updateInBoard() override;

		void drawInBoard() const override;

	};
}