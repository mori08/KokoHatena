#include "Board.hpp"
#include "../../../Config/Config.hpp"
#include "../../../MyLibrary/MyLibrary.hpp"

namespace 
{
	/// <summary>
	/// �t���[���㕔�̑���Ղ̍���
	/// </summary>
	int32 controlFrameHeight()
	{
		static const int32 CONTROL_FRAME_HEIGHT = Kokoha::Config::get<int32>(U"Board.controlFrameHeight");
		return CONTROL_FRAME_HEIGHT;
	}
}

namespace Kokoha
{
	Board::Board(Role role, const String& name, const Size& size)
		: m_role(role)
		, m_name(name)
		, m_pos(Scene::Center() - size/2) // ��ʒ��S�ɕ\��
		, m_size(size + Point::Down(controlFrameHeight()))
		, m_render(size)
	{
		
	}

	const Board::BoardRequest& Board::input()
	{
		movePosByCursor();

		return inputInBoard();
	}

	void Board::update()
	{
		updateInBoard();
	}

	void Board::draw() const
	{
		// �t���[���̑���
		static const double FRAME_THICKNESS = Config::get<double>(U"Board.frameThickness");

		// �����_�[�e�N�X�`���[�̃N���A
		m_render.clear(MyBlack);

		// �����_�[�e�N�X�`���[���g���� Rect(m_pos + Point::Down(controlFrameHeight()), m_size) �ɕ`��
		{
			ScopedRenderTarget2D target(m_render);

			// �{�[�h���̕`��
			drawInBoard();
		}
		Graphics2D::Flush();
		m_render.resolve();
		m_render.draw(m_pos + Point::Down(controlFrameHeight()));

		// �t���[���̕`��
		Rect(m_pos, m_size).drawFrame(FRAME_THICKNESS, 0, MyWhite);
		// �t���[���㕔�̑����
		Rect(m_pos, m_size.x, controlFrameHeight()).draw(MyWhite);
	}

	Vec2 Board::cursorPosFInBoard() const
	{
		return Cursor::PosF() - m_pos - Point::Down(controlFrameHeight());
	}

	void Board::movePosByCursor()
	{
		ClearPrint();
		Print << m_optMovePos;

		if (MouseL.up())
		{
			m_optMovePos = none;
			return;
		}

		if (Rect(m_pos, m_size.x, controlFrameHeight()).leftClicked())
		{
			m_optMovePos = Cursor::Pos() - m_pos;
		}

		if (!m_optMovePos) { return; }

		m_pos = Cursor::Pos() - m_optMovePos.value();
		m_pos.x = Clamp(m_pos.x, 0, Scene::Size().x - m_size.x);
		m_pos.y = Clamp(m_pos.y, 0, Scene::Size().y - m_size.y);
	}
}