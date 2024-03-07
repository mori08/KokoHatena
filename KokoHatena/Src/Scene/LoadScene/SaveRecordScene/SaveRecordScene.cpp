#include"SaveRecordScene.hpp"

namespace Kokoha
{
	SaveRecordScene::SaveRecordScene(const InitData& init)
		: LoadScene(init)
	{
		const std::list<RecordSet>& recordSetList = getData().recordSetList;

		setLoadThread
		(
			[&recordSetList]()
			{
				TextWriter writer(RecordSet::FILE_NAME);

				// RecordSetを文字列に変換して1行ずつ書き込む
				for (const auto& recordSet : recordSetList)
				{
					writer.writeln(recordSet.encryption());
				}

				return SceneName::LOAD_BOARD;
			}
		);
	}
}
