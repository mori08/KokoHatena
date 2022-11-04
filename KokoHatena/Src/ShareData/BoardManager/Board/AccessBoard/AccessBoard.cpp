#include"AccessBoard.hpp"

namespace Kokoha
{
	AccessBoard::AccessBoard()
		: Board(BoardRole::ACCESS
			, U"AccessBoard"
			, BoardState::IS_HIDING
		)
		, m_terrain(U"asset/data/test.csv")
	{
	}

	void AccessBoard::receiveRequest(const String&)
	{
	}

	void AccessBoard::inputInBoard()
	{
	}

	void AccessBoard::updateInBoard(BoardRequest&)
	{
	}

	void AccessBoard::drawInBoard() const
	{
		m_terrain.draw();
	}
}