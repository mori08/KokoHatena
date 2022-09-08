#include "SelectRecordScene.hpp"
#include "../../Config/Config.hpp"

namespace Kokoha
{
	SelectRecordScene::SelectRecordScene(const InitData& init, const RecordBox& recordBox, std::function<void(const RecordSet& recordSet)> recordFunc, const String& explanation, SceneName sceneName)
		: IScene(init)
		, m_explanation(explanation)
		, m_sceneName(sceneName)
		, m_wheel(0)
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
			if (itr->update())
			{
				changeScene(m_sceneName);
			}
		}

		scrollWheel();
	}

	void SelectRecordScene::draw() const
	{		
		FontAsset(U"15")(m_explanation).draw();

		int32 index = 0;

		for (const auto& recordBox : m_recordBoxList)
		{
			recordBox.draw(index++);
		}
	}

	void SelectRecordScene::scrollWheel()
	{
		m_wheel += Mouse::Wheel();

		while (m_wheel > 1)
		{
			++m_topBoxItr;
			if (m_topBoxItr == m_recordBoxList.end()) { --m_topBoxItr; }
			--m_wheel;
		}

		while (m_wheel < -1)
		{
			if (m_topBoxItr != m_recordBoxList.begin()) { --m_topBoxItr; }
			++m_wheel;
		}
	}

	SelectLoadRecordScene::SelectLoadRecordScene(const InitData& init)
		: SelectRecordScene(
			init,
			RecordBox([this]() {getData().nowRecordSet = RecordSet(); }, { U"",U"はじめから" }),
			[this](const RecordSet& recordSet) { getData().nowRecordSet = recordSet; },
			U"ロードするデータを選択してください",
			SceneName::TITLE
		)
	{

	}
}