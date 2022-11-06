#include"AccessBoard.hpp"
#include"AccessObject/PlayerAccessObject/PlayerAccessObject.hpp"

namespace Kokoha
{
	AccessBoard::AccessBoard()
		: Board(BoardRole::ACCESS
			, U"AccessBoard"
			, BoardState::IS_HIDING
		)
		, m_terrain(U"asset/data/test.csv")
	{
		AccessObject::Ptr ptr = std::make_unique<PlayerAccessObject>(Vec2(25, 25) / 2);
		m_objectMap.try_emplace(ptr->guid(), std::move(ptr));
	}

	void AccessBoard::receiveRequest(const String&)
	{
	}

	void AccessBoard::inputInBoard()
	{
		for (const auto& object : m_objectMap)
		{
			object.second->input(cursorPosFInBoard());
		}
	}

	void AccessBoard::updateInBoard(BoardRequest&)
	{
		for (const auto& object : m_objectMap)
		{
			object.second->update(m_terrain);
		}
	}

	void AccessBoard::drawInBoard() const
	{
		m_terrain.draw();

		for (const auto& object : m_objectMap)
		{
			object.second->draw();
		}
	}
}