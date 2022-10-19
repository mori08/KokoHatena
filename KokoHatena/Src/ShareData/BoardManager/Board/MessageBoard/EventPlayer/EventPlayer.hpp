#pragma once

#include "EventObject/EventObject.hpp"

namespace Kokoha
{
	/// <summary>
	/// �I�u�W�F�N�g�ƃC�x���g�̊Ǘ��ƍĐ�
	/// </summary>
	class EventPlayer
	{
	private:

		// �`��͈�
		const MSRenderTexture m_render;

		// �Ǎ����̃C�x���g
		TOMLTableArrayIterator m_now;

		// �Ǎ����̃C�x���g��end�̃C�e���[�^
		TOMLTableArrayIterator m_end;

		// �C�x���g��TOML�t�@�C��
		const TOMLReader m_eventToml;

		// �I�u�W�F�N�g�̃��X�g
		std::map<String, std::unique_ptr<EventObject>> m_objectList;

	public:

		/// <param name="eventFileName"> �C�x���g�̃t�@�C���� </param>
		/// <param name="drawSize"> �`��͈� </param>
		EventPlayer(const String& eventFileName, const Size& drawSize);

		/// <summary>
		/// �X�V
		/// </summary>
		void update();

		/// <summary>
		/// �`��
		/// </summary>
		/// <param name="drawPos"> �`����W </param>
		void draw(const Point& drawPos) const;

	};
}