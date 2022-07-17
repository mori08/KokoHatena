#include"LoadRecordScene.hpp"

namespace Kokoha
{
	LoadRecordScene::LoadRecordScene(const InitData& init)
		: LoadScene(init)
	{
		RecordManager& recordManager = getData().record;
		BoardManager& boardManager = getData().board;

		setLoadThread
		(
			[&recordManager, &boardManager]()
			{
				const RecordManager::LoadResult loadResult = recordManager.load();

				// セーブデータの読み込みに失敗したとき
				if (loadResult == RecordManager::LoadResult::ERROR) { return SceneName::TITLE; }

				recordManager.writeDebugText();

				// 各レコードに合わせてManagerの読み込みを行う
				boardManager.load(recordManager);

				return SceneName::DESKTOP;
			}
		);
	}
}