#include "LoadBoardScene.hpp"

namespace Kokoha
{
	LoadBoardScene::LoadBoardScene(const InitData& init)
		: LoadScene(init)
	{
		RecordSet& nowRecordSet = getData().nowRecordSet;
		BoardManager& boardManager = getData().board;

#ifdef _DEBUG
		getData().nowRecordSet.writeDebugText();
#endif // _DEBUG

		setLoadThread
		(
			[&nowRecordSet, &boardManager]()
			{
				boardManager.load(nowRecordSet);

				return SceneName::DESKTOP;
			}
		);
	}
}
