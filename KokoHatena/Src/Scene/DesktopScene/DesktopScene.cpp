#include"DesktopScene.hpp"

namespace Kokoha
{
	DesktopScene::DesktopScene(const InitData& init)
		: IScene(init)
	{
		
	}

	void DesktopScene::update()
	{
		if (Optional<SceneName> sceneName = getData().board.update(getData().nowRecordSet))
		{
			changeScene(sceneName.value());
		}
	}

	void DesktopScene::draw() const
	{
		getData().board.draw();
	}
}