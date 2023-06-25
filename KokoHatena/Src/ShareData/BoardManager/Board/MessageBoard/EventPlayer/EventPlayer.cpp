#include "EventPlayer.hpp"
#include "EventObject/TextureEventObject/TextureEventObject.hpp"
#include "../../../../../MyLibrary/MyLibrary.hpp"

namespace Kokoha
{
	EventPlayer::EventPlayer(const String& eventFileName, const Size& drawSize, const RecordSet& recordSet)
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
			BoardRequest tmp; // ���ō쐬�i�������Ń��N�G�X�g�͑���Ȃ��j
			playEvent(*init_now, tmp);
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
		while (!m_waitingObjectList.empty() && !m_waitingObjectList.front()->wait())
		{
			m_waitingObjectList.pop_front();
		}
		
		// �C�x���g�̐i�s
		if (m_now != m_end && m_waitingObjectList.empty())
		{
			const String eventName = (*m_now)[U"event"].getString();
			
			playEvent(*m_now, boardRequest);

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

	void EventPlayer::playEvent(const TOMLValue& nowEvent, BoardRequest& boardRequest)
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

		// �I�u�W�F�N�g�ւ̖���
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
			m_waitingObjectList.emplace_back(objectPtr);

			return;
		}

		// jamp���Ɏg�p����t���O�̐ݒ�
		if (eventName == U"flag")
		{
			const String name  = nowEvent[U"name"].getString();
			const bool   value = nowEvent[U"value"].getOr<bool>(true);

			m_jampFlagMap[name] = value;

			return;
		}

		// �ʃC�x���g�Q�ւ̑J��
		if (eventName == U"jamp")
		{
			const String to = nowEvent[U"to"].getString();
			const String flag = nowEvent[U"flag"].getString();

			if (!m_eventToml[to].isTableArray())
			{
				throw Error(U"EventPlayer: jamp: �w�肳�ꂽ�J�ڐ�to[" + to + U"]�͑��݂��Ȃ�");
			}

			if (flag == U"" || (m_jampFlagMap.count(flag) && m_jampFlagMap[flag]))
			{
				m_now = m_eventToml[to].tableArrayView().begin();
				m_end = m_eventToml[to].tableArrayView().end();
			}

			return;
		}

		// ���{�[�h�ւ̃��N�G�X�g
		if (eventName == U"board")
		{
			const String role = nowEvent[U"role"].getString();
			const String text = nowEvent[U"text"].getString();
			
			if (!BOARD_ROLE_MAP.count(role))
			{
				throw Error(U"EventPlayer: board: �w�肳�ꂽBoardRole[" + role + U"]�����݂��Ȃ�");
			}

			boardRequest.toBoard.emplace_back(BOARD_ROLE_MAP.find(role)->second, text);

			return;
		}

		// �V�[���ւ̃��N�G�X�g
		if (eventName == U"scene")
		{
			const String scene = nowEvent[U"scene"].getString();

			if (!SCENE_NAME_MAP.count(scene))
			{
				throw Error(U"EventPlayer: scene: �w�肳�ꂽScene[" + scene + U"]�͑��݂��Ȃ�");
			}

			boardRequest.toScene = SCENE_NAME_MAP.find(scene)->second;

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