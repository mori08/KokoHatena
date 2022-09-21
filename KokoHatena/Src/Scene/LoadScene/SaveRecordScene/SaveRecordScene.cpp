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

				// RecordSet‚ğ•¶š—ñ‚É•ÏŠ·‚µ‚Ä1s‚¸‚Â‘‚«‚Ş
				for (const auto& recordSet : recordSetList)
				{
					writer.writeln(recordSet.encryption());
				}

				return SceneName::TITLE;
			}
		);
	}
}