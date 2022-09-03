#include "RecordBox.hpp"
#include "../../../Config/Config.hpp"
#include "../../../MyLibrary/MyLibrary.hpp"

namespace Kokoha
{
	RecordBox::RecordBox(std::function<void()> onSelected, const std::pair<String, String>& textPair)
		: m_onSelected(onSelected)
		, m_textPair(textPair)
	{
		// ��ʓ���RecordBox�̍��W�̈�ԏ�
		static const Point DRAW_POS = Config::get<Point>(U"SelectRecordScene.drawPos");
		m_pos.x = DRAW_POS.x;
		m_pos.y = Scene::Height();
	}

	void RecordBox::update()
	{
		// ���W�̍X�V
		static const double MOVE_RATE_POS = Config::get<double>(U"RecordBox.posMoveRate");
		internalDividingPoint(m_pos, m_goal, MOVE_RATE_POS);

		if (m_pos.distanceFrom(m_goal) < 1e-5 && RectF(m_goal, getSize()).leftClicked())
		{
			m_onSelected();
		}
	}

	void RecordBox::setGoalPos(const int32 index)
	{
		// ��ʓ���RecordBox�̍��W�̈�ԏ�
		static const Point DRAW_POS = Config::get<Point>(U"SelectRecordScene.drawPos");
		// RecordBox��
		static const int32 DRAW_SPACE = Config::get<int32>(U"SelectRecordScene.recordBoxSpace");

		// ��ʏ㑤�ɉB��
		if (index < 0)
		{
			setGoalPos(Vec2(DRAW_POS.x, -DRAW_SPACE - RecordBox::getSize().y));
			return;
		}

		const Vec2 pos = DRAW_POS + index * Vec2::Down(DRAW_SPACE + RecordBox::getSize().y);

		// ��ʉ����ɉB��
		if (pos.y + getSize().y > Scene::Height())
		{
			setGoalPos(Vec2(DRAW_POS.x, Scene::Height() + DRAW_SPACE));
			return;
		}

		// ��ʓ��ɕ\��
		setGoalPos(pos);
	}

	void RecordBox::setGoalPos(const Vec2& pos)
	{
		m_goal = pos;
	}

	void RecordBox::draw() const
	{
		// m_textPair.first��\��������W
		static const Point TEXT_FIRST_POS = Config::get<Point>(U"RecordBox.textFirstPos");
		// m_textPair.seoncd��\��������W
		static const Point TEXT_SECOND_POS = Config::get<Point>(U"RecordBox.textSecondPos");
		// ���E�̘g�̌���
		static const int32 FRAME_WIDTH = Config::get<int32>(U"RecordBox.frameWith");

		// m_textPair�̕`��
		FontAsset(U"20")(m_textPair.first ).draw(m_pos + TEXT_FIRST_POS );
		FontAsset(U"20")(m_textPair.second).draw(m_pos + TEXT_SECOND_POS);

		// �����̃t���[��
		RectF(
			m_pos + Point::Left(FRAME_WIDTH / 2),
			FRAME_WIDTH, getSize().y
		).draw(MyWhite);

		// �E���̃t���[��
		RectF(
			m_pos + Point::Left(FRAME_WIDTH / 2 - getSize().x),
			FRAME_WIDTH, getSize().y
		).draw(MyWhite);
	}

	const Size& RecordBox::getSize()
	{
		// �`�悷��T�C�Y
		static const Size SIZE = Config::get<Size>(U"RecordBox.size");
		return SIZE;
	}
}