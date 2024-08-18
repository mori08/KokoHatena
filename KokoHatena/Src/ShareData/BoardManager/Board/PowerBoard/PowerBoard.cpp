#include "PowerBoard.hpp"
#include "../../../../Config/Config.hpp"
#include "../../../../MyLibrary/MyLibrary.hpp"

namespace Kokoha
{
	PowerBoard::PowerBoard()
		: Board(
			BoardRole::POWER,
			U"PowerBoard",
			BoardState::IS_HIDING
		)
		, m_requestOpt(none)
	{
	}

	void PowerBoard::receiveRequest(const String&)
	{
	}

	void PowerBoard::inputInBoard()
	{
		if (yesButton().contains(boardArg().cursorPos()) && boardArg().rect().leftClicked())
		{
			m_requestOpt = BoardRequest();
			m_requestOpt->toScene = SceneName::TITLE;
		}

		if (noButton().contains(boardArg().cursorPos()) && boardArg().rect().leftClicked())
		{
			m_requestOpt = BoardRequest();
			m_requestOpt->toBoard.emplace_back(BoardRole::POWER, U"hide");
		}
	}

	void PowerBoard::updateInBoard(BoardRequest& request)
	{
		if (m_requestOpt)
		{
			request = m_requestOpt.value();
			m_requestOpt = none;
		}
	}

	void PowerBoard::drawInBoard() const
	{
		static const Point TEXT_POS = Config::get<Point>(U"SecurityBoard.textPos");

		FontAsset(U"20")(U"タイトルにもどりますか？").drawAt(TEXT_POS, MyWhite);
		FontAsset(U"20")(U"はい").drawAt(yesButton().center(), MyWhite);
		FontAsset(U"20")(U"いいえ").drawAt(noButton().center(), MyWhite);
	}

	const Rect& PowerBoard::yesButton() const
	{
		static const Rect rtn = Config::get<Rect>(U"PowerBoard.selectYes");
		return rtn;
	}

	const Rect& PowerBoard::noButton() const
	{
		static const Rect rtn = Config::get<Rect>(U"PowerBoard.selectNo");
		return rtn;
	}
}
