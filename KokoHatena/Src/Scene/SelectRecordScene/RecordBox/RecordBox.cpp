#include "RecordBox.hpp"
#include "../../../Config/Config.hpp"
#include "../../../MyLibrary/MyLibrary.hpp"

namespace Kokoha
{
	/// <summary>
	/// �����̎擾
	/// </summary>
	int32 getHeight()
	{
		// �`�悷��T�C�Y
		static const int32 rtn = Config::get<int32>(U"RecordBox.height");
		return rtn;
	}

	/// <summary>
	/// ��\�����̕��̎擾
	/// </summary>
	double getHideWidth()
	{
		// �`�悷��T�C�Y
		static const double rtn = Config::get<int32>(U"RecordBox.hideWidth");
		return rtn;
	}

	/// <summary>
	/// �\�����̕��̎擾
	/// </summary>
	double getDisplayWidth()
	{
		// �`�悷��T�C�Y
		static const double rtn = Config::get<int32>(U"RecordBox.displayWidth");
		return rtn;
	}

	/// <summary>
	/// �I�𒆂̕��̎擾
	/// </summary>
	double getOverWidth()
	{
		// �`�悷��T�C�Y
		static const double rtn = Config::get<int32>(U"RecordBox.overWidth");
		return rtn;
	}

	/// <summary>
	/// �`�悷��͈́i�T�C�Y�j�̎擾
	/// </summary>
	/// <returns> �`�悷��͈� </returns>
	double gethideWidth()
	{
		// �`�悷��T�C�Y
		static const int32 rtn = Config::get<int32>(U"RecordBox.hideWidth");
		return rtn;
	}

	/// <summary>
	/// �I��p�̃{�^���̒����`
	/// </summary>
	/// <returns></returns>
	const RectF& getButtonRect()
	{
		static const RectF rtn = Config::get<RectF>(U"RecordBox.button");
		return rtn;
	}

	RecordBox::RecordBox(std::function<void()> onSelected, const std::pair<String, String>& textPair)
		: m_width(0)
		, m_onSelected(onSelected)
		, m_textPair(textPair)
	{
		// ��ʓ���RecordBox�̍��W�̈�ԏ�
		static const Point DRAW_POS = Config::get<Point>(U"SelectRecordScene.drawPos");

		m_pos.x = DRAW_POS.x;
		m_pos.y = Scene::Height();
	}

	bool RecordBox::update()
	{
		// ���W�̍X�V
		static const double MOVE_RATE_POS = Config::get<double>(U"RecordBox.posMoveRate");
		internalDividingPoint(m_pos, m_goal, MOVE_RATE_POS);

		updateWidth();

		if (m_width > getButtonRect().tr().x && getButtonRect().movedBy(m_pos).leftClicked())
		{
			m_onSelected();
			return true;
		}

		return false;
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
			setGoalPos(Vec2(DRAW_POS.x, -DRAW_SPACE - getHeight()));
			return;
		}

		const Vec2 pos = DRAW_POS + index * Vec2::Down(DRAW_SPACE + getHeight());

		// ��ʉ����ɉB��
		if (pos.y + getHeight() > Scene::Height())
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

	void RecordBox::draw(int32 index) const
	{
		// �ԍ���\��������W
		static const Point TEXT_FILE_POS = Config::get<Point>(U"RecordBox.textFilePos");
		// m_textPair.first��\��������W
		static const Point TEXT_FIRST_POS = Config::get<Point>(U"RecordBox.textFirstPos");
		// m_textPair.seoncd��\��������W
		static const Point TEXT_SECOND_POS = Config::get<Point>(U"RecordBox.textSecondPos");
		// ���E�̘g�̌���
		static const double FRAME_WIDTH = Config::get<int32>(U"RecordBox.frameWith");
		// �w�i�ɕ`�悷����W
		static const ColorF BACK_COLOR = Config::get<ColorF>(U"RecordBox.backColor");

		// �w�i
		RectF(m_pos, m_width, getHeight()).draw(BACK_COLOR);

		// �e�L�X�g
		FontAsset(U"18")(U"File " + ToString(index)).draw(m_pos + TEXT_FILE_POS);
		FontAsset(U"12")(m_textPair.first ).draw(m_pos + TEXT_FIRST_POS );
		FontAsset(U"20")(m_textPair.second).draw(m_pos + TEXT_SECOND_POS);

		// �{�^��
		const Rect button = getButtonRect().movedBy(m_pos).draw(MyBlack);
		button.draw(MyBlack);
		if (m_width > getButtonRect().tr().x && button.mouseOver())
		{
			static const RectF buttonLight = Config::get<RectF>(U"RecordBox.buttonLight");
			buttonLight.movedBy(m_pos).draw(BACK_COLOR);
		}

		// �������B��
		RectF(m_pos + Vec2::Right(m_width), getOverWidth(), getHeight()).draw(MyBlack);

		// �����̃t���[��
		RectF(
			m_pos + Vec2::Left(FRAME_WIDTH / 2),
			FRAME_WIDTH, getHeight()
		).draw(MyWhite);

		// �E���̃t���[��
		RectF(
			m_pos + Vec2::Left(FRAME_WIDTH / 2 - m_width),
			FRAME_WIDTH, getHeight()
		).draw(MyWhite);
	}

	void RecordBox::updateWidth()
	{
		double goalWidth = 0;

		// ��ʊO
		if (m_goal.y < 0 || m_goal.y > Scene::Height())
		{
			goalWidth = getHideWidth();
		}

		// �}�E�X���I�[�o�[���Ă���
		else if (RectF(m_goal, m_width, getHeight()).mouseOver())
		{
			goalWidth = getOverWidth();
		}

		// ��ʓ�
		else
		{
			goalWidth = getDisplayWidth();
		}

		// ���̍X�V
		static const double MOVE_RATE_POS = Config::get<double>(U"RecordBox.posMoveRate");
		internalDividingPoint(m_width, goalWidth, MOVE_RATE_POS);
	}
}