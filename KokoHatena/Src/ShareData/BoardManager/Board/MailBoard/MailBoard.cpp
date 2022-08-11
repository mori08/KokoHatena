#include "MailBoard.hpp"
#include "../../../../Config/Config.hpp"

namespace Kokoha
{
	MailBoard::MailBoard()
		: Board(Role::MAIL
			, U"MailBoard"
			, State::IS_HIDING
		)
	{
	}

	void MailBoard::receiveRequest(const String&)
	{

	}

	Board::BoardRequest MailBoard::inputInBoard()
	{
		return none;
	}

	void MailBoard::updateInBoard()
	{
	}

	void MailBoard::drawInBoard() const
	{
	}

}