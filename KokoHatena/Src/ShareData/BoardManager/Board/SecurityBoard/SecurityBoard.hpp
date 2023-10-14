#pragma once
#include "../Board.hpp"
#include "../../../RecordSet/RecordSet.hpp"

namespace Kokoha
{
	class SecurityBoard : public Board
	{
	private:

	public:

		SecurityBoard(const RecordSet& recordSet);

	private:

		void receiveRequest(const String& requestText) override;

		void inputInBoard() override;

		void updateInBoard(BoardRequest& request) override;

		void drawInBoard() const override;

	};
}
