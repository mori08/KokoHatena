#include"AccessBoard.hpp"

namespace Kokoha
{
	AccessBoard::AccessBoard()
		: Board(Role::ACCESS
			, U"AccessBoard"
			, State::IS_HIDING
		)
	{
	}

	void AccessBoard::receiveRequest(const String&)
	{
	}

	Board::BoardRequest AccessBoard::inputInBoard()
	{
		return none;
	}

	void AccessBoard::updateInBoard()
	{
	}

	void AccessBoard::drawInBoard() const
	{
	}
}