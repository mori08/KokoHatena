#include"DesktopScene.hpp"

namespace Kokoha
{
	DesktopScene::DesktopScene(const InitData& init)
		: IScene(init)
		, m_board(Board::Role::MAIL, U"Test", Size(300,200))
	{

	}

	void DesktopScene::update()
	{
		m_board.input();
	}

	void DesktopScene::draw() const
	{
		m_board.draw();
	}
}