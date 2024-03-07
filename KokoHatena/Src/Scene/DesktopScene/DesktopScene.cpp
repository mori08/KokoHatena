#include"DesktopScene.hpp"

namespace Kokoha
{
	DesktopScene::DesktopScene(const InitData& init)
		: IScene(init)
	{
#ifdef _DEBUG
		getData().nowRecordSet.writeDebugText();
#endif // _DEBUG
	}

	void DesktopScene::update()
	{
		if (Optional<SceneName> sceneName = getData().board.update(getData().nowRecordSet))
		{
			int32 day = getData().nowRecordSet.getRecord(U"Day");
			getData().nowRecordSet.setRecord(U"Day", day + 1);
			changeScene(sceneName.value());
		}
	}

	void DesktopScene::draw() const
	{
		getData().board.draw();
	}
}
