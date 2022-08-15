#pragma once
#include"Board/Board.hpp"
#include"../RecordSet/RecordSet.hpp"

namespace Kokoha
{
	/// <summary>
	/// �{�[�h�̊Ǘ����s��
	/// loadScene�ł̏�����
	/// DesktopScene�ł̍X�V�ƕ`��
	/// </summary>
	class BoardManager
	{
	private:

		// �{�[�h�̃��X�g
		std::list<std::unique_ptr<Board>> m_boardList;

	public:

		BoardManager();

	public:

		/// <summary>
		/// Record����
		/// </summary>
		/// <param name="recordSet"> �Z�[�u�f�[�^ </param>
		void load(RecordSet& recordSet);

		/// <summary>
		/// �X�V
		/// </summary>
		void update();

		/// <summary>
		/// �`��
		/// </summary>
		void draw() const;

	private:

		/// <summary>
		/// Board::Role�ɑΉ������{�[�h�̃C�e���[�^���擾
		/// </summary>
		/// <param name="role"> �{�[�h�̎�� </param>
		std::list<std::unique_ptr<Board>>::iterator findBoardItr(const Board::Role& role);

		/// <summary>
		/// �{�[�h��擪�ɕ\��
		/// </summary>
		/// <param name="role"> �{�[�h�̎�� </param>
		/// <param name="requestText"> �J�����Ƃ�request�𓊂��� </param>
		void displayBoard(const Board::Role& role, const String& requestText = U"");

		/// <summary>
		/// �{�[�h�𖖔��Ɉړ�������\��
		/// </summary>
		/// <param name="role"> �{�[�h�̎�� </param>
		void hideBoard(const Board::Role& role);

	};
}