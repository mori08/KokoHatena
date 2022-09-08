#include "SelectRecordScene.hpp"
#include "../../Config/Config.hpp"
#include "../../MyLibrary/MyLibrary.hpp"

namespace Kokoha
{
	SelectRecordScene::SelectRecordScene(const InitData& init, const RecordBox& recordBox, std::function<void(const RecordSet& recordSet)> recordFunc, const String& explanation, SceneName sceneName)
		: IScene(init)
		, m_explanation(explanation)
		, m_sceneName(sceneName)
		, m_scrollBarPosY(Scene::Center().y)
		, m_wheel(0)
	{
		// �擪��RecordBox�ɒǉ�
		m_recordBoxList.emplace_back(recordBox);

		// RecordSet�ɑΉ�����
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
			// �擪��RecordBox�� recordBoxIndex = 0
			// ����ȍ~��1�����₷
			if (itr == m_topBoxItr || recordBoxIndex >= 0) { ++recordBoxIndex; }

			// RecordBox�̍X�V
			itr->setGoalPos(recordBoxIndex);
			if (itr->update())
			{
				changeScene(m_sceneName);
			}
		}

		scrollWheel();

		// �X�N���[���o�[�̃T�C�Y
		static const Size SCROLL_BAR_SIZE = Config::get<Size>(U"SelectRecordScene.scrollBarSize");
		// �X�N���[���o�[�̃T�C�Y
		static const double SCROLL_BAR_MOVE_RATE = Config::get<double>(U"SelectRecordScene.scrollBarMoveRate");

		// �X�N���[���o�[��y���W
		const double scrollBarGoalY 
			= Scene::Center().y
			- SCROLL_BAR_SIZE.y/2
			+ SCROLL_BAR_SIZE.y * (m_recordBoxList.size() - recordBoxIndex - 0.5) / m_recordBoxList.size();

		// �X�N���[���o�[��y���W
		internalDividingPoint(
			m_scrollBarPosY,
			scrollBarGoalY,
			SCROLL_BAR_MOVE_RATE
		);

		ClearPrint();
		Print << U"";
		Print << U"�N���b�N : " << (MouseL.pressed() ? U"1" : U"");
		Print << U"�z�C�[�� : " << (Mouse::Wheel()==0 ? String(U"") : ToString(Mouse::Wheel()));
	}

	void SelectRecordScene::draw() const
	{		
		FontAsset(U"15")(m_explanation).draw();

		int32 index = 0;

		for (const auto& recordBox : m_recordBoxList)
		{
			recordBox.draw(index++);
		}

		// �X�N���[���o�[��x���W
		static const int32 SCROLL_BAR_POS_X = Config::get<int32>(U"SelectRecordScene.scrollBarPosX");
		// �X�N���[���o�[�̃T�C�Y
		static const Size SCROLL_BAR_SIZE = Config::get<Size>(U"SelectRecordScene.scrollBarSize");
		// �X�N���[���o�[�̕�
		static const int32 SCROLL_BAR_WIDTH = Config::get<int32>(U"SelectRecordScene.scrollBarWidth");

		// �X�N���[���o�[�̕`��
		Rect(Arg::center = Point(SCROLL_BAR_POS_X, Scene::Center().y), SCROLL_BAR_SIZE)
			.draw(MyWhite);

		RectF(
			Arg::center = Vec2(SCROLL_BAR_POS_X, m_scrollBarPosY),
			SCROLL_BAR_WIDTH
		).draw(MyWhite);
	}

	void SelectRecordScene::scrollWheel()
	{
		// �z�C�[���ł̓����̑傫��
		static const double WHEEL_RATE = Config::get<double>(U"SelectRecordScene.wheelRate");

		m_wheel += WHEEL_RATE * Mouse::Wheel();

		// �X�N���[���o�[�ł̓����̑傫��
		static const double BAR_RATE = Config::get<double>(U"SelectRecordScene.barRate");
		// �X�N���[���o�[��x���W
		static const int32 SCROLL_BAR_POS_X = Config::get<int32>(U"SelectRecordScene.scrollBarPosX");
		// �X�N���[���o�[�̕�
		static const int32 SCROLL_BAR_WIDTH = Config::get<int32>(U"SelectRecordScene.scrollBarWidth");
		// �X�N���[���o�[�̃T�C�Y
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
			RecordBox([this]() {getData().nowRecordSet = RecordSet(); }, { U"",U"�͂��߂���" }),
			[this](const RecordSet& recordSet) { getData().nowRecordSet = recordSet; },
			U"���[�h����f�[�^��I�����Ă�������",
			SceneName::TITLE
		)
	{

	}
}