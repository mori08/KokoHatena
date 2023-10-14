#include "SecurityBoard.hpp"

namespace Kokoha
{
	SecurityBoard::SecurityBoard(const RecordSet& recordSet)
		: Board(BoardRole::SECURITY
			, U"SerucityBoard"
			, BoardState::IS_HIDING)
	{
	}

	void SecurityBoard::receiveRequest(const String& requestText)
	{
	}

	void SecurityBoard::inputInBoard()
	{
	}

	void SecurityBoard::updateInBoard(BoardRequest& request)
	{
	}

	void SecurityBoard::drawInBoard() const
	{
	}
}
