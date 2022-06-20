#include"DesktopScene.hpp"

namespace Kokoha
{
	DesktopScene::DesktopScene(const InitData& init)
		: IScene(init)
		, m_board(Board::Role::MAIL, U"Test", Size(200,200))
	{

	}

	void DesktopScene::update()
	{

	}

	void DesktopScene::draw() const
	{
		m_board.draw();
	}
}