#include "EventPlayer.hpp"
#include "EventObject/TextureEventObject/TextureEventObject.hpp"
#include "../../../../../MyLibrary/MyLibrary.hpp"

namespace Kokoha
{
	EventPlayer::EventPlayer(const String& eventFileName, const Size& drawSize)
		: m_render(drawSize)
		, m_eventToml(eventFileName)
	{
		setGenerateObjectMap();

		// TODO �C�x���g�����������𑖂点��
		m_now = m_eventToml[U"init"].tableArrayView().begin();
		m_end = m_eventToml[U"init"].tableArrayView().end();

		// ������
		TOMLTableArrayIterator init_now = m_now;
		TOMLTableArrayIterator init_end = m_end;
		while (init_now != init_end)
		{
			playEvent(*init_now);
			++init_now;
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
			const String eventName = (*m_now)[U"event"].getString();
			
			playEvent(*m_now);

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

	void EventPlayer::playEvent(const TOMLValue& nowEvent)
	{
		const String eventName = nowEvent[U"event"].getString(); // �C�x���g��

		// �I�u�W�F�N�g�̐���
		if (eventName == U"object")
		{
			const String type = nowEvent[U"type"].getString();
			const String name = nowEvent[U"name"].getString();
			const TOMLValue param = nowEvent[U"param"];

			if (!m_generateObjectMap.count(type))
			{
				throw Error(U"EventPlayer: object: ���݂��Ȃ�type[" + type + U"]���w�肳��Ă���");
			}

			if (m_objectList.count(name))
			{
				throw Error(U"EventPlayer: object: ���ɑ��݂���name[" + name + U"]���w�肳��Ă���");
			}

			m_objectList[name] = m_generateObjectMap[type](param);

			return;
		}

		if (eventName == U"act")
		{
			const String name = nowEvent[U"name"].getString();
			const TOMLValue param = nowEvent[U"param"];
			
			if (!m_objectList.count(name))
			{
				throw Error(U"EventPlayer: act: ���݂��Ȃ�object��name[" + name + U"]���w�肳��Ă���");
			}

			const ObjectPtr objectPtr = m_objectList[name];
			
			objectPtr->receive(param);
			m_waitingObject.emplace_back(objectPtr);

			return;
		}

		// �ʃC�x���g�Q�ւ̑J��
		if (eventName == U"jamp")
		{
			const String to = nowEvent[U"to"].getString();

			if (!m_eventToml[to].isTableArray())
			{
				throw Error(U"EventPlayer: jamp: �w�肳�ꂽ�J�ڐ�[" + to + U"]�͑��݂��Ȃ�");
			}

			m_now = m_eventToml[to].tableArrayView().begin();
			m_end = m_eventToml[to].tableArrayView().end();

			return;
		}

		throw Error(U"EventPlayer: event[" + eventName + U"]�͑��݂��Ȃ�");
	}

	void EventPlayer::setGenerateObjectMap()
	{
		m_generateObjectMap[U"texture"] = [](const TOMLValue& param)
		{
			return std::make_shared<TextureEventObject>(param);
		};
	}
}