#include"AccessBoard.hpp"

namespace Kokoha
{
	AccessBoard::AccessBoard()
		: Board(BoardRole::ACCESS
			, U"AccessBoard"
			, BoardState::IS_HIDING
		)
	{
	}

	void AccessBoard::receiveRequest(const String&)
	{
	}

	void AccessBoard::inputInBoard()
	{
	}

	void AccessBoard::updateInBoard(BoardRequest& request)
	{
	}

	void AccessBoard::drawInBoard() const
	{
	}
}