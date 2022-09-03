#pragma once

#include<Siv3D.hpp>

namespace Kokoha
{
	/// <summary>
	/// RecordSet�̑I��/�`��
	/// </summary>
	class RecordBox
	{
	private:

		// ���W
		Vec2 m_pos;

		// ���W�̈ړ���
		Vec2 m_goal;

		// �I�����ꂽ�Ƃ��̏���
		const std::function<void()> m_onSelected;

		// �\�����镶����
		const std::pair<String, String> m_textPair;

	public:

		/// <param name="onSelected"> �I�����ꂽ�Ƃ��̏��� </param>
		/// <param name="itr"> RecordSet�̃C�e���[�^ </param>
		RecordBox(std::function<void()> onSelected, const std::pair<String, String>& textPair);

		/// <summary>
		/// �X�V
		/// </summary>
		void update();

		/// <summary>
		/// ���W�̈ړ����ݒ�
		/// </summary>
		/// <param name="index"> �\�����鏇�� </param>
		void setGoalPos(const int32 index);

		/// <summary>
		/// ���W�̈ړ����ݒ�
		/// </summary>
		/// <param name="pos"> ���W�̈ړ��� </param>
		void setGoalPos(const Vec2& pos);

		/// <summary>
		/// �`��
		/// </summary>
		void draw() const;

		/// <summary>
		/// �`�悷��͈́i�T�C�Y�j�̎擾
		/// </summary>
		/// <returns> �`�悷��͈� </returns>
		static const Size& getSize();

	};
}