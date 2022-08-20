#include"LoadRecordScene.hpp"

namespace Kokoha
{
	LoadRecordScene::LoadRecordScene(const InitData& init)
		: LoadScene(init)
	{
		std::list<RecordSet>& recordSetList = getData().recordSetList;

		setLoadThread
		(
			[&recordSetList]()
			{
				TextReader reader(RecordSet::FILE_NAME);

				// �t�@�C�������݂��Ȃ��Ƃ� -> ���X�g����̂܂܏I��
				if (!reader) { return SceneName::SELECT_LOAD_RECORD; }

				// 1�s����RecordSet�ɕϊ�����
				while (Optional<String> line = reader.readLine())
				{
					if (Optional<RecordSet> recordSetOpt = RecordSet::decryption(line.value()))
					{
						recordSetList.emplace_back(recordSetOpt.value());
					}
				}

				return SceneName::SELECT_LOAD_RECORD;
			}
		);
	}
}