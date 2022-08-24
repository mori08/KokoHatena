#include "SelectLoadRecordScene.hpp"

namespace Kokoha
{
	SelectLoadRecordScene::SelectLoadRecordScene(const InitData& init)
		: SelectRecordScene(init)
	{
		int32 index = 0;

		for (auto& recordSet : getData().recordSetList)
		{
			RecordBox recordBox(
				getRecordBoxPos(index++),
				[this, &recordSet]() {getData().nowRecordSet = recordSet; },
				{ recordSet.getTimeCode(), U"Day" + ToString(recordSet.getRecord(U"Day")) }
			);

			m_recordBoxList.emplace_back(std::move(recordBox));
		}
	}

	void SelectLoadRecordScene::update()
	{
		SelectRecordScene::update();
	}

	void SelectLoadRecordScene::draw() const
	{
		SelectRecordScene::draw();
	}
}