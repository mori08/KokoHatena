#pragma once

#include <Siv3D.hpp>

namespace Kokoha
{
	/// <summary>
	/// EventPlayer�ŕ\������I�u�W�F�N�g
	/// </summary>
	class EventObject
	{
	public:

		virtual ~EventObject() = default;

		/// <summary>
		/// ���߂��󂯎���Ԃ�ω�������
		/// </summary>
		/// <param name="parameter"> �p�����[�^�ƂȂ�toml�I�u�W�F�N�g </param>
		virtual void receive(const TOMLValue& parameter) = 0;

		/// <summary>
		/// �I�u�W�F�N�g���C�x���g�S�̂�҂����邩�̏���
		/// </summary>
		/// <returns> true �̂Ƃ��҂����� , false �̂Ƃ��C�x���g��i�܂��� </returns>
		virtual bool wait() = 0;

		/// <summary>
		/// �X�V
		/// </summary>
		virtual void update() = 0;

		/// <summary>
		/// �`��
		/// </summary>
		virtual void draw() const = 0;

	};
}