#include "MessageBoard.hpp"
#include "../../../../Config/Config.hpp"

namespace Kokoha
{
	MessageBoard::MessageBoard()
		: Board(Role::MESSAGE
			, U"MessageBoard"
			, State::IS_HIDING
		)
	{
	}

	void MessageBoard::receiveRequest(const String&)
	{

	}

	Board::BoardRequest MessageBoard::inputInBoard()
	{
		return none;
	}

	void MessageBoard::updateInBoard()
	{
	}

	void MessageBoard::drawInBoard() const
	{
	}

}