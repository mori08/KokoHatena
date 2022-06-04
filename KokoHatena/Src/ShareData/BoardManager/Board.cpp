#include "Board.hpp"
#include "../../Config/Config.hpp"
#include "../../MyLibrary/MyLibrary.hpp"

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

	void Board::input()
	{
		inputInBoard();
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
}