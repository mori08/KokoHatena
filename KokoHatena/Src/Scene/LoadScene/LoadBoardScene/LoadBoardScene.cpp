#include "LoadBoardScene.hpp"

namespace Kokoha
{
	LoadBoardScene::LoadBoardScene(const InitData& init)
		: LoadScene(init)
	{
		RecordSet& nowRecordSet = getData().nowRecordSet;
		BoardManager& boardManager = getData().board;

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