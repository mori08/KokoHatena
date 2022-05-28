#include "Board.hpp"

namespace Kokoha
{
	Board::Board(Role role, const String& name, const Size& size)
		: m_role(role)
		, m_name(name)
		, m_pos(Scene::Center() - size/2) // âÊñ íÜêSÇ…ï\é¶
		, m_size(size)
	{

	}

	void Board::input()
	{
		inputInBoard();
	}

	void Board::update()
	{
		updateInBoard();
	}

	void Board::draw() const
	{
		drawInBoard();
	}
}