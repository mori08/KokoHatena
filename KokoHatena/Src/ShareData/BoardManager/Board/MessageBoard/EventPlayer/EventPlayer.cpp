#include "EventPlayer.hpp"
#include "../../../../../MyLibrary/MyLibrary.hpp"

namespace Kokoha
{
	EventPlayer::EventPlayer(const String& eventFileName, const Size& drawSize)
		: m_render(drawSize)
		, m_eventToml(eventFileName)
	{
		// TODO �C�x���g�����������𑖂点��
		m_now = m_eventToml[U"example"].tableArrayView().begin();
		m_end = m_eventToml[U"example"].tableArrayView().end();
	}

	void EventPlayer::update()
	{
		if (m_now != m_end)
		{

			++m_now;
		}

		// �I�u�W�F�N�g�̍X�V
		for (const auto& object : m_objectList)
		{
			object.second->update();
		}
	}

	void EventPlayer::draw(const Point& drawPos) const
	{
		// �����_�[�e�N�X�`���[�̃N���A
		m_render.clear(MyBlack);

		// �����_�[�e�N�X�`���[���g���� Rect(drawPos, m_render.size()) �ɕ`��
		{
			ScopedRenderTarget2D target(m_render);

			// �I�u�W�F�N�g�̕`��
			for (const auto& object : m_objectList)
			{
				object.second->draw();
			}
		}

		Graphics2D::Flush();
		m_render.resolve();
		m_render.draw(drawPos);
	}
}