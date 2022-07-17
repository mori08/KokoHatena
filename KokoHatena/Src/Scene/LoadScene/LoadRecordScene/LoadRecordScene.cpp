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

				// �Z�[�u�f�[�^�̓ǂݍ��݂Ɏ��s�����Ƃ�
				if (loadResult == RecordManager::LoadResult::ERROR) { return SceneName::TITLE; }

				recordManager.writeDebugText();

				// �e���R�[�h�ɍ��킹��Manager�̓ǂݍ��݂��s��
				boardManager.load(recordManager);

				return SceneName::DESKTOP;
			}
		);
	}
}