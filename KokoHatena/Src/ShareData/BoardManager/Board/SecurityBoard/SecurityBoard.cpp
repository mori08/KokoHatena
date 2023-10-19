#include "SecurityBoard.hpp"
#include "../../../../Config/Config.hpp"

namespace Kokoha
{

	SecurityBoard::SecurityBoard(const RecordSet& recordSet)
		: Board(BoardRole::SECURITY
			, U"SecurityBoard"
			, BoardState::IS_HIDING)
	{
		setState(U"test");
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
		ClearPrint();
		Print << m_text;
		for (const auto& select : m_selectList)
		{
			Print << select.text;
		}
	}

	void SecurityBoard::setState(const String& stateName)
	{
		const TOMLValue toml = Config::toml()[U"SecurityBoard"][stateName];
		m_text = toml[U"text"].getString();

		if (!toml[U"select"].isTableArray()) { return; }

		for (const TOMLValue& selectToml : toml[U"select"].tableArrayView())
		{
			const String selectText = selectToml[U"text"].getString();
			std::list<std::pair<BoardRole, String>> toBoard;

			for (const TOMLValue& toBoardToml : selectToml[U"toBoard"].tableArrayView())
			{
				const String boardRoleName = toBoardToml[U"role"].getString();
				const auto roleItr = BOARD_ROLE_MAP.find(boardRoleName);
				if (roleItr == BOARD_ROLE_MAP.end())
				{
					continue;
					throw Error(U"Faild to find [" + boardRoleName + U"] board");
				}

				const BoardRole boardRole = roleItr->second;
				const String requestText = toBoardToml[U"request"].getString();
			}

			m_selectList.emplace_back(selectText, toBoard);
		}
	}
}
