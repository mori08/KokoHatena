#include "RecordBox.hpp"
#include "../../../Config/Config.hpp"
#include "../../../MyLibrary/MyLibrary.hpp"

namespace Kokoha
{
	RecordBox::RecordBox(const Vec2& pos, std::function<void()> onSelected, const std::pair<String, String>& textPair)
		: m_pos(pos)
		, m_goal(pos)
		, m_onSelected(onSelected)
		, m_textPair(textPair)
	{

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