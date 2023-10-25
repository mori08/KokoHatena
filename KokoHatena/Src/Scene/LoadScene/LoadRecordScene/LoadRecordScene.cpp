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
				recordSetList.clear();

				TextReader reader(RecordSet::FILE_NAME);

				// ファイルが存在しないとき -> リストが空のまま終了
				if (!reader) { return SceneName::SELECT_LOAD_RECORD; }

				// 1行ずつRecordSetに変換する
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
