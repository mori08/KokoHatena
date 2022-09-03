#include "SelectRecordScene.hpp"
#include "../../Config/Config.hpp"

namespace Kokoha
{
	SelectRecordScene::SelectRecordScene(const InitData& init, const RecordBox& recordBox, std::function<void(const RecordSet& recordSet)> recordFunc, const String& explanation)
		: IScene(init)
		, m_explanation(explanation)
	{
		// 先頭にRecordBoxに追加
		m_recordBoxList.emplace_back(recordBox);

		// RecordSetに対応する
		for (const auto& recordSet : getData().recordSetList)
		{
			m_recordBoxList.emplace_back
			(
				[recordFunc, &recordSet]() { recordFunc(recordSet); },
				std::pair<String, String>(recordSet.getTimeCode(), U"Day" + ToString(recordSet.getRecord(U"Day")))
			);
		}

		m_topBoxItr = m_recordBoxList.begin();
	}

	void SelectRecordScene::update()
	{
		int32 recordBoxIndex = -1;
		
		for (auto itr = m_recordBoxList.begin(); itr != m_recordBoxList.end(); ++itr)
		{
			// 先頭のRecordBoxを recordBoxIndex = 0
			// それ以降は1ずつ増やす
			if (itr == m_topBoxItr || recordBoxIndex >= 0) { ++recordBoxIndex; }

			// RecordBoxの更新
			itr->setGoalPos(recordBoxIndex);
			itr->update();
		}

		// 一番上のRecordBoxを1つ先へ
		if (KeyW.down())
		{
			if (m_topBoxItr != m_recordBoxList.begin()) { --m_topBoxItr; }
		}

		// 一番上のRecordBoxを1つ後へ
		if (KeyS.down())
		{
			++m_topBoxItr;
			if (m_topBoxItr == m_recordBoxList.end()) { --m_topBoxItr; }
		}
	}

	void SelectRecordScene::draw() const
	{		
		FontAsset(U"15")(m_explanation).draw();

		for (const auto& recordBox : m_recordBoxList)
		{
			recordBox.draw();
		}
	}

	SelectLoadRecordScene::SelectLoadRecordScene(const InitData& init)
		: SelectRecordScene(
			init,
			RecordBox([this]() {getData().nowRecordSet = RecordSet(); }, { U"",U"はじめから" }),
			[this](const RecordSet& recordSet) { getData().nowRecordSet = recordSet; },
			U"ロードするデータを選択してください"
		)
	{

	}
}