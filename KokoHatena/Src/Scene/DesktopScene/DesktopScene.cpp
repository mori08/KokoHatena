#include"DesktopScene.hpp"

namespace Kokoha
{
	DesktopScene::DesktopScene(const InitData& init)
		: IScene(init)
	{
		
	}

	void DesktopScene::update()
	{
		getData().board.update();
	}

	void DesktopScene::draw() const
	{
		getData().board.draw();
	}
}