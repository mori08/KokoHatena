#include "Board.hpp"
#include "../../Config/Config.hpp"
#include "../../MyLibrary/MyLibrary.hpp"

namespace Kokoha
{
	Board::Board(Role role, const String& name, const Size& size)
		: m_role(role)
		, m_name(name)
		, m_pos(Scene::Center() - size/2) // ��ʒ��S�ɕ\��
		, m_size(size)
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

		// �����_�[�e�N�X�`���[���g���� Rect(m_pos, m_size) �ɕ`��
		{
			ScopedRenderTarget2D target(m_render);

			// �{�[�h���̕`��
			drawInBoard();

			// �t���[���̕`��
			Rect(Point::Zero(), m_size).drawFrame(FRAME_THICKNESS, 0, MyWhite);
		}

		// �����_�[�e�N�X�`���̕`��
		Graphics2D::Flush();
		m_render.resolve();
		m_render.draw(m_pos);
	}
}