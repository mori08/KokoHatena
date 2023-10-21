#include "SecurityBoard.hpp"
#include "../../../../Config/Config.hpp"
#include "../../../../MyLibrary/MyLibrary.hpp"

namespace Kokoha
{
	void SecurityBoard::Select::setRect(const Point& center)
	{
		static const Size SELECT_SIZE = Config::get<Size>(U"SecurityBoard.selectSize");
		m_rect = Rect(Arg::center = center, SELECT_SIZE);
	}

	void SecurityBoard::Select::draw() const
	{
		FontAsset(U"20")(text).drawAt(m_rect.center(), MyWhite);
	}

	bool SecurityBoard::Select::clicked(const Point& cursorPos) const
	{
		return m_rect.contains(cursorPos) && MouseL.down();
	}

	SecurityBoard::SecurityBoard(const RecordSet& recordSet)
		: Board(BoardRole::SECURITY
			, U"SecurityBoard"
			, BoardState::IS_HIDING)
	{
		setState(U"test");
	}

	void SecurityBoard::receiveRequest(const String& requestText)
	{
		setState(requestText);
	}

	void SecurityBoard::inputInBoard()
	{
		const Point cursorPos = cursorPosInBoard();
		for (const auto& select : m_selectList)
		{
			if (!select.clicked(cursorPos)) { continue; }

			// 選択肢がクリックされたらBoardRequestへ
			m_requestOpt = BoardRequest();
			m_requestOpt->toBoard = select.toBoard;
		}
	}

	void SecurityBoard::updateInBoard(BoardRequest& request)
	{
		if (m_requestOpt)
		{
			request = m_requestOpt.value();
			m_requestOpt = none;
		}
	}

	void SecurityBoard::drawInBoard() const
	{
		// m_text を描画する座標
		static const Point TEXT_POS = Config::get<Point>(U"SecurityBoard.textPos");

		FontAsset(U"20")(m_text).drawAt(TEXT_POS);

		for (const auto& select : m_selectList)
		{
			select.draw();
		}
	}

	void SecurityBoard::setState(const String& stateName)
	{
		const TOMLValue toml = Config::toml()[U"SecurityBoard"][stateName];

		if (!toml.isTable()) { return; }

		m_text = toml[U"text"].getString();
		m_selectList.clear();

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
				toBoard.emplace_back(boardRole, requestText);
			}

			m_selectList.emplace_back(selectText, toBoard);
		}

		// Boardの幅
		static const int32 BOARD_WIDTH = Config::get<int32>(U"SecurityBoard.size.x");
		// 選択肢を表示するy座標
		static const int32 SELECT_Y = Config::get<int32>(U"SecurityBoard.selectY");

		const int32 n = 1 + (int32)m_selectList.size();
		int32 i = 0;
		for (Select& select : m_selectList)
		{
			++i;
			select.setRect(Point(BOARD_WIDTH * i / n, SELECT_Y));
		}
	}
}
