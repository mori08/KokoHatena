#include "EventPlayer.hpp"
#include "EventObject/TextureEventObject/TextureEventObject.hpp"
#include "../../../../../MyLibrary/MyLibrary.hpp"

namespace Kokoha
{
	EventPlayer::EventPlayer(const String& eventFileName, const Size& drawSize)
		: m_render(drawSize)
		, m_eventToml(eventFileName)
	{
		setEventMap();
		setGenerateObjectMap();

		// TODO �C�x���g�����������𑖂点��
		m_now = m_eventToml[U"init"].tableArrayView().begin();
		m_end = m_eventToml[U"init"].tableArrayView().end();

		while (m_now != m_end)
		{
			m_eventMap[(*m_now)[U"event"].getString()](*m_now);
			++m_now;
		}
	}

	void EventPlayer::input()
	{
		// �I�u�W�F�N�g�̓���
		for (const auto& object : m_objectList)
		{
			object.second->input();
		}
	}

	void EventPlayer::update(BoardRequest& boardRequest)
	{
		// �I�u�W�F�N�g�̍X�V
		for (const auto& object : m_objectList)
		{
			object.second->update();
		}

		// �I�u�W�F�N�g�̑҂���Ԃ̉���
		while (!m_waitingObject.empty() && !m_waitingObject.front()->wait())
		{
			m_waitingObject.pop_front();
		}

		// �C�x���g�̐i�s
		if (m_now != m_end && m_waitingObject.empty())
		{
			m_eventMap[(*m_now)[U"event"].getString()](*m_now);
			++m_now;
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

	void EventPlayer::setEventMap()
	{
		// �I�u�W�F�N�g�̐���
		m_eventMap[U"object"] = [this](const TOMLValue& object)
		{
			const String type = object[U"type"].getString();
			const String name = object[U"name"].getString();
			const TOMLValue param = object[U"param"];

			if (!m_generateObjectMap.count(type))
			{
				throw Error(U"EventPlayer: object: ���݂��Ȃ�type���w�肳��Ă���");
			}

			if (m_objectList.count(name))
			{
				throw Error(U"EventPlayer: object: ���ɑ��݂���name���w�肳��Ă���");
			}

			m_objectList[name] = m_generateObjectMap[type](param);
		};
	}

	void EventPlayer::setGenerateObjectMap()
	{
		m_generateObjectMap[U"texture"] = [](const TOMLValue& param)
		{
			return std::make_shared<TextureEventObject>(param);
		};
	}
}