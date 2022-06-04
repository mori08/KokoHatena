#pragma once
#include<Siv3D.hpp>

namespace Kokoha
{
	/// <summary>
	/// �{�[�h�̊��
	/// </summary>
	class Board
	{
	public:

		/// <summary>
		/// ��ށi�����j
		/// </summary>
		enum class Role
		{
			MAIL,     // ���[��
			SECURITY, // �Z�L�����e�B
			ACCESS,   // �A�N�Z�X�i�p�Y���A�N�V���������j
		};

	private:

		// ���
		const Role m_role;

		// ���O
		const String m_name;

		// ����̍��W
		Point m_pos;

		// �T�C�Y
		const Size m_size;

		// �����_�[�e�N�X�`���[�i�{�[�h���̕`��j
		const MSRenderTexture m_render;

	public:

		Board(Role role, const String& name, const Size& size);

		virtual ~Board() = default;

	public:

		/// <summary>
		/// ����
		/// </summary>
		void input();

		/// <summary>
		/// �X�V
		/// </summary>
		void update();

		/// <summary>
		/// �`��
		/// </summary>
		void draw() const;

	protected:

		/// <summary>
		/// �e�{�[�h�ŗL�̓��͏���
		/// </summary>
		virtual void inputInBoard() {};

		/// <summary>
		/// �e�{�[�h�ŗL�̍X�V����
		/// </summary>
		virtual void updateInBoard() {};

		/// <summary>
		/// �e�{�[�h�ŗL�̕`�揈��
		/// </summary>
		virtual void drawInBoard() const { Circle(0, 0, 200).draw(); };

	};
}