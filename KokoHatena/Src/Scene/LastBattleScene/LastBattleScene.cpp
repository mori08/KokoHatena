#include "LastBattleScene.hpp"

namespace Kokoha
{
	LastBattleScene::LastBattleScene(const InitData& init)
		: IScene(init)
		, m_accessBoard(U"last")
	{

	}

	void LastBattleScene::update()
	{
		m_accessBoard.input();

		BoardRequest boardRequest;
		m_accessBoard.update(boardRequest);
	}

	void LastBattleScene::draw() const
	{
		m_accessBoard.draw();
	}
}
