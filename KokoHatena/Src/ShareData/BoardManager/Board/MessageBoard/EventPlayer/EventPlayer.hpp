#pragma once

#include "EventObject/EventObject.hpp"
#include "../../BoardConst.hpp"
#include "../../../../RecordSet/RecordSet.hpp"

namespace Kokoha
{
	/// <summary>
	/// �I�u�W�F�N�g�ƃC�x���g�̊Ǘ��ƍĐ�
	/// </summary>
	class EventPlayer
	{
	private:

		// EventObject��shared_ptr
		using ObjectPtr = std::shared_ptr<EventObject>;

	private:

		// �`��͈�
		const MSRenderTexture m_render;

		// �Ǎ����̃C�x���g
		TOMLTableArrayIterator m_now;

		// �Ǎ����̃C�x���g��end�̃C�e���[�^
		TOMLTableArrayIterator m_end;

		// �C�x���g��TOML�t�@�C��
		const TOMLReader m_eventToml;

		// �����񂩂�I�u�W�F�N�g�̍쐬�ւ̕R�Â�
		std::unordered_map<String, std::function<ObjectPtr(const TOMLValue&)>> m_generateObjectMap;

		// �I�u�W�F�N�g�̃��X�g
		std::map<String, ObjectPtr> m_objectList;

		// �҂���Ԃ̃I�u�W�F�N�g
		std::list<ObjectPtr> m_waitingObjectList;

		// ��ʑJ�ڏ����̃t���O�̃��X�g
		std::unordered_map<String, bool> m_jampFlagMap;

	public:

		/// <param name="eventFileName"> �C�x���g�̃t�@�C���� </param>
		/// <param name="drawSize"> �`��͈� </param>
		EventPlayer(const String& eventFileName, const Size& drawSize, const RecordSet& recordSet);

		/// <summary>
		/// ����
		/// </summary>
		void input();

		/// <summary>
		/// �X�V
		/// </summary>
		/// <param name=boardRequest"> �{�[�h�ւ̃��N�G�X�g </param>
		void update(BoardRequest& boardRequest);

		/// <summary>
		/// �`��
		/// </summary>
		/// <param name="drawPos"> �`����W </param>
		void draw(const Point& drawPos) const;

	private:

		/// <summary>
		/// �C�x���g�̎��s
		/// </summary>
		/// <param name="nowEvent"> ���ݓǂݍ��ݒ��̃C�x���g </param>
		/// <param name="boardRequest"> �{�[�h�O�ւ̃��N�G�X�g </param>
		/// <returns> true �̂Ƃ��C�x���g��i�߂� , jamp�ȊO�͊�{�I��true��ݒ� </returns>
		bool playEvent(const TOMLValue& nowEvent, BoardRequest& boardRequest);

		/// <summary>
		/// �I�u�W�F�N�g�̐����̊֐��̓o�^
		/// </summary>
		void setGenerateObjectMap();

	};
}
