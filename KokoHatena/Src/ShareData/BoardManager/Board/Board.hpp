#pragma once
#include"../../../MyLibrary/SliceTexture/SliceTexture.hpp"
#include"../../../Scene/SceneName.hpp"

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
			MESSAGE,  // ���b�Z�[�W
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

		/// <summary>
		/// �O���֑��M����f�[�^
		/// </summary>
		class Request
		{
		public:

			// ���{�[�h�ւ̖���
			std::list<std::pair<Role, String>> toBoard;

			// Record�ւ̏�������
			std::unordered_map<String, int32> toRecord;

			// Scene�J��
			Optional<SceneName> toScene = none;
		};

	private:

		// ���
		const Role m_role;

		// ���
		State m_state;

		// ���O
		const String m_name;

		// �T�C�Y
		const Size m_size;

		// ����̍��W
		Point m_pos;

		// �����_�[�e�N�X�`���[�i�{�[�h���̕`��j
		const MSRenderTexture m_render;

		// ���W�ړ����̊���W (none�̂Ƃ��ړ����Ȃ�)
		Optional<Point> m_optMovePos;

		// �A�C�R���摜�̖��O
		String m_iconTextureName;

		// �A�C�R���̕\����(-1���Ɣ�\��)
		const int32 m_iconOrder;

	public:

		/// <param name="role"> ���(����) </param>
		/// <param name="configName"> config�t�@�C���ł̖��O </param>
		/// <param name="state"> ������� </param>
		Board(const Role& role, const String& configName, const State& state);

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
		/// �A�C�R�����N���b�N���ꂽ��
		/// </summary>
		/// <returns> 
		/// �ȉ��̏�����S�Ė������Ƃ� true , ����ȊO�̏ꍇfalse
		/// * �A�C�R�����N���b�N���ꂽ
		/// * m_state��NONE�łȂ�
		/// * m_iconOrder��-1�łȂ�
		/// </returns>
		bool onIconClicked() const;

		/// <summary>
		/// �{�[�h���N���b�N���ꂽ��
		/// </summary>
		/// <returns>
		/// m_state��DISPLAYED ���� �{�[�h���N���b�N���ꂽ�Ƃ� true , �����łȂ��Ƃ� false
		/// </returns>
		bool mouseLeftDown() const;

		/// <summary>
		/// �A�C�R���̕`��
		/// </summary>
		void drawIcon() const;

		/// <summary>
		/// ����
		/// </summary>
		/// <returns> true �̂Ƃ��{�[�h����� </returns>
		bool input();

		/// <summary>
		/// �X�V
		/// </summary>
		/// <param name="request"> �{�[�h�O���ւ̖��� </param>
		void update(Request& request);

		/// <summary>
		/// �`��
		/// </summary>
		void draw() const;

		/// <summary>
		/// ���{�[�h����f�[�^�̎�M
		/// </summary>
		/// <param name="requestText"> �f�[�^�ƂȂ镶���� </param>
		virtual void receiveRequest(const String& requestText) = 0;

	protected:

		/// <summary>
		/// �e�{�[�h�ŗL�̓��͏���
		/// </summary>
		virtual void inputInBoard() = 0;

		/// <summary>
		/// �e�{�[�h�ŗL�̍X�V����
		/// </summary>
		virtual void updateInBoard(Request& request) = 0;

		/// <summary>
		/// �e�{�[�h�ŗL�̕`�揈��
		/// </summary>
		virtual void drawInBoard() const = 0;

	protected:

		/// <summary>
		/// �{�[�h�̃T�C�Y���擾
		/// </summary>
		/// <returns> �T�C�Y </returns>
		const Size& size() const
		{
			return m_size;
		}

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

		/// <summary>
		/// �A�C�R���͈̔͂̎擾
		/// </summary>
		/// <returns> �A�C�R���͈̔͂̒����` </returns>
		const Rect getIconRect() const;

		/// <summary>
		/// ��\���{�^���͈̔͂����������`�̎擾
		/// </summary>
		/// <returns> ��\���{�^���͈̔� </returns>
		const Rect hideButtonRect() const;

	};
}