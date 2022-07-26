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

		/// <summary>
		/// ���
		/// </summary>
		enum class State
		{
			IS_DISPLAYED, // �\����
			IS_HIDING,    // ��\��
			NONE,         // ���p�s��
		};

		// ���{�[�h�ɑ΂��Ẵf�[�^���M
		using BoardRequest = Optional<const std::pair<Role, String>>;

	private:

		// ���
		const Role m_role;

		// ���
		State m_state;

		// ���O
		const String m_name;

		// ����̍��W
		Point m_pos;

		// �T�C�Y
		const Size m_size;

		// �����_�[�e�N�X�`���[�i�{�[�h���̕`��j
		const MSRenderTexture m_render;

		// ���W�ړ����̊���W (none�̂Ƃ��ړ����Ȃ�)
		Optional<Point> m_optMovePos;

	public:

		Board(Role role, const String& name, const Size& size);

		virtual ~Board() = default;

	public:

		/// <summary>
		/// �{�[�h�̎�ނ̎擾
		/// </summary>
		/// <returns> �{�[�h�̎�� </returns>
		const Role& role() const
		{
			return m_role;
		}

		/// <summary>
		/// �{�[�h�̏�Ԃ̎擾
		/// </summary>
		/// <returns> �{�[�h�̏�� </returns>
		const State& state() const
		{
			return m_state;
		}

		/// <summary>
		/// �{�[�h��\�������Ԃ֕ύX
		/// </summary>
		void display()
		{
			m_state = State::IS_DISPLAYED;
		}

		/// <summary>
		/// �{�[�h���\���ɂ����Ԃ֕ύX
		/// </summary>
		void hide()
		{
			m_state = State::IS_HIDING;
		}

		/// <summary>
		/// ����
		/// </summary>
		/// <returns> �{�[�h�ւ̖��� </returns>
		const BoardRequest& input();

		/// <summary>
		/// �X�V
		/// </summary>
		void update();

		/// <summary>
		/// �`��
		/// </summary>
		void draw() const;

		/// <summary>
		/// ���{�[�h����f�[�^�̎�M
		/// </summary>
		/// <param name="requestText"> �f�[�^�ƂȂ镶���� </param>
		virtual void receiveRequest(const String& requestText) const {}

	protected:

		/// <summary>
		/// �e�{�[�h�ŗL�̓��͏���
		/// </summary>
		virtual const BoardRequest& inputInBoard() { return none; };

		/// <summary>
		/// �e�{�[�h�ŗL�̍X�V����
		/// </summary>
		virtual void updateInBoard() {};

		/// <summary>
		/// �e�{�[�h�ŗL�̕`�揈��
		/// </summary>
		virtual void drawInBoard() const {};

	protected:

		/// <summary>
		/// �{�[�h���̃}�E�X���W�̎擾
		/// </summary>
		/// <returns> �{�[�h���̃}�E�X���W </returns>
		Point cursorPosInBoard() const
		{
			return cursorPosFInBoard().asPoint();
		}

		/// <summary>
		/// �{�[�h���̃}�E�X���W�̎擾
		/// </summary>
		/// <returns> �{�[�h���̃}�E�X���W </returns>
		Vec2 cursorPosFInBoard() const;

	private:

		/// <summary>
		/// �J�[�\���ō��W���ړ�����
		/// </summary>
		void movePosByCursor();

	};
}