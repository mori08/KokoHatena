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

	void AccessBoard::inputInBoard()
	{
	}

	void AccessBoard::updateInBoard(Request& request)
	{
	}

	void AccessBoard::drawInBoard() const
	{
	}
}