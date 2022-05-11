#include"LoadRecordScene.hpp"

namespace Kokoha
{
	LoadRecordScene::LoadRecordScene(const InitData& init)
		: LoadScene(init)
	{
		RecordManager& recordManager = getData().record;

		setLoadThread
		(
			[&recordManager]()
			{
				const RecordManager::LoadResult loadResult = recordManager.load();

				// セーブデータの読み込みに失敗したとき
				if (loadResult == RecordManager::LoadResult::ERROR) { return SceneName::TITLE; }

				recordManager.writeDebugText();

				return SceneName::DESKTOP;
			}
		);
	}
}