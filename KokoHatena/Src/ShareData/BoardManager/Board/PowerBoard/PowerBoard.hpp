#pragma once
#include "../Board.hpp"

namespace Kokoha
{
	class PowerBoard : public Board
	{
	private:

		Optional<BoardRequest> m_requestOpt;

	public:

		PowerBoard();

	private:

		void receiveRequest(const String&) override;

		void inputInBoard() override;

		void updateInBoard(BoardRequest& request) override;

		void drawInBoard() const override;

	private:

		const Rect& yesButton() const;

		const Rect& noButton() const;

	};
}
