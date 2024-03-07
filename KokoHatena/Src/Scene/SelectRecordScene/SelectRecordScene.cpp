#include "SelectRecordScene.hpp"
#include "../../Config/Config.hpp"
#include "../../MyLibrary/MyLibrary.hpp"

namespace Kokoha
{
	SelectRecordScene::SelectRecordScene(
		const InitData& init,
		const String& explanation
	)
		: IScene(init)
		, m_explanation(explanation)
		, m_scrollBarPosY(Scene::Center().y)
		, m_wheel(0)
	{

	}

	void SelectRecordScene::initRecordBox()
	{
		m_topBoxItr = m_recordBoxList.begin();

		int32 recordBoxIndex = 0;

		for (auto itr = m_recordBoxList.begin(); itr != m_recordBoxList.end(); ++itr)
		{
			itr->setPos(recordBoxIndex);
			++recordBoxIndex;
		}
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
			if (const auto sceneName = itr->update())
			{
				changeScene(sceneName.value());
			}
		}

		scrollWheel();

		// スクロールバーのサイズ
		static const Size SCROLL_BAR_SIZE = Config::get<Size>(U"SelectRecordScene.scrollBarSize");
		// スクロールバーのサイズ
		static const double SCROLL_BAR_MOVE_RATE = Config::get<double>(U"SelectRecordScene.scrollBarMoveRate");

		// スクロールバーのy座標
		const double scrollBarGoalY 
			= Scene::Center().y
			- SCROLL_BAR_SIZE.y/2
			+ SCROLL_BAR_SIZE.y * (m_recordBoxList.size() - recordBoxIndex - 0.5) / m_recordBoxList.size();

		// スクロールバーのy座標
		internalDividingPoint(
			m_scrollBarPosY,
			scrollBarGoalY,
			SCROLL_BAR_MOVE_RATE
		);
	}

	void SelectRecordScene::draw() const
	{		
		FontAsset(U"15")(m_explanation).draw();

		// 描画するファイル番号

		for (const auto& recordBox : m_recordBoxList)
		{
			recordBox.draw();
		}

		// スクロールバーのx座標
		static const int32 SCROLL_BAR_POS_X = Config::get<int32>(U"SelectRecordScene.scrollBarPosX");
		// スクロールバーのサイズ
		static const Size SCROLL_BAR_SIZE = Config::get<Size>(U"SelectRecordScene.scrollBarSize");
		// スクロールバーの幅
		static const int32 SCROLL_BAR_WIDTH = Config::get<int32>(U"SelectRecordScene.scrollBarWidth");

		// スクロールバーの描画
		Rect(Arg::center = Point(SCROLL_BAR_POS_X, Scene::Center().y), SCROLL_BAR_SIZE)
			.draw(MyWhite);

		RectF(
			Arg::center = Vec2(SCROLL_BAR_POS_X, m_scrollBarPosY),
			SCROLL_BAR_WIDTH
		).draw(MyWhite);
	}

	void SelectRecordScene::scrollWheel()
	{
		// ホイールでの動きの大きさ
		static const double WHEEL_RATE = Config::get<double>(U"SelectRecordScene.wheelRate");

		m_wheel += WHEEL_RATE * Mouse::Wheel();

		// スクロールバーでの動きの大きさ
		static const double BAR_RATE = Config::get<double>(U"SelectRecordScene.barRate");
		// スクロールバーのx座標
		static const int32 SCROLL_BAR_POS_X = Config::get<int32>(U"SelectRecordScene.scrollBarPosX");
		// スクロールバーの幅
		static const int32 SCROLL_BAR_WIDTH = Config::get<int32>(U"SelectRecordScene.scrollBarWidth");
		// スクロールバーのサイズ
		static const Size SCROLL_BAR_SIZE = Config::get<Size>(U"SelectRecordScene.scrollBarSize");

		if (MouseL.pressed() 
			&& Abs(SCROLL_BAR_POS_X - Cursor::Pos().x) < SCROLL_BAR_WIDTH / 2
			&& Abs(m_scrollBarPosY - Cursor::Pos().y) > SCROLL_BAR_SIZE.y / m_recordBoxList.size())
		{
			double w = Cursor::PosF().y - m_scrollBarPosY;
			m_wheel += Scene::DeltaTime() * BAR_RATE * (w == 0 ? 0 : w / Abs(w));
		}
		
		while (m_wheel >= 1)
		{
			++m_topBoxItr;
			if (m_topBoxItr == m_recordBoxList.end()) { --m_topBoxItr; }
			--m_wheel;
		}

		while (m_wheel <= -1)
		{
			if (m_topBoxItr != m_recordBoxList.begin()) { --m_topBoxItr; }
			++m_wheel;
		}
	}

	SelectLoadRecordScene::SelectLoadRecordScene(const InitData& init)
		: SelectRecordScene(
			init,
			U"ロードするデータを選択してください"
		)
	{
		for (auto& recordSet : getData().recordSetList)
		{
			m_recordBoxList.emplace_back
			(
				RecordBox(
					[this, &recordSet]() {
						getData().nowRecordSet = recordSet;
						return SceneName::LOAD_BOARD;
					},
					{recordSet.getTimeCode(), U"Day"+ToString(recordSet.getRecord(U"Day"))}
				)
			);
		}

		m_recordBoxList.emplace_back(
			RecordBox(
				[this]() { getData().nowRecordSet = RecordSet(); return SceneName::LOAD_BOARD; },
				{U"", U"はじめから"}
			)
		);

		initRecordBox();
	}

	SelectSaveRecordScene::SelectSaveRecordScene(const InitData& init)
		: SelectRecordScene(
			init,
			U"セーブするデータを選択してください"
		)
	{
		for (auto& recordSet : getData().recordSetList)
		{
			m_recordBoxList.emplace_back
			(
				RecordBox(
					[this, &recordSet]() {
						recordSet = getData().nowRecordSet.setRecordTime();
						return SceneName::SAVE_RECORD;
					},
					{ recordSet.getTimeCode(), U"Day" + ToString(recordSet.getRecord(U"Day")) }
				)
			);
		}

		m_recordBoxList.emplace_back(
			RecordBox(
				[this]() {
					getData().recordSetList.emplace_front(getData().nowRecordSet.setRecordTime());
					return SceneName::SAVE_RECORD;
				},
				{ U"", U"新しいデータ" }
			)
		);

		m_recordBoxList.emplace_back(
			RecordBox(
				[this]() {
					return SceneName::LOAD_BOARD;
				},
				{ U"", U"セーブしない" }
			)
		);

		initRecordBox();
	}
}
