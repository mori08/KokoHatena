#pragma once
#include"../Board.hpp"

namespace Kokoha
{
	class MailBoard : public Board
	{
	public:

		MailBoard();

	private:

		void receiveRequest(const String& requestText) override;

		BoardRequest inputInBoard() override;

		void updateInBoard() override;

		void drawInBoard() const override;

	};
}