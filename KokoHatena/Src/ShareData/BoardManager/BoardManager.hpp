#pragma once
#include"Board/Board.hpp"
#include"../RecordSet/RecordSet.hpp"
#include"../../Scene/SceneName.hpp"

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
		void load(const RecordSet& recordSet);

		/// <summary>
		/// �X�V
		/// </summary>
		/// <param name="recordSet"> �Z�[�u�f�[�^ </param>
		Optional<SceneName> update(RecordSet& recordSet);

		/// <summary>
		/// �`��
		/// </summary>
		void draw() const;

	private:

		/// <summary>
		/// Board::Role�ɑΉ������{�[�h�̃C�e���[�^���擾
		/// </summary>
		/// <param name="role"> �{�[�h�̎�� </param>
		std::list<std::unique_ptr<Board>>::iterator findBoardItr(const BoardRole& role);

		/// <summary>
		/// �{�[�h��擪�ɕ\��
		/// </summary>
		/// <param name="role"> �{�[�h�̎�� </param>
		/// <param name="requestText"> �J�����Ƃ�request�𓊂��� </param>
		void displayBoard(const BoardRole& role, const String& requestText = U"");

		/// <summary>
		/// �{�[�h�𖖔��Ɉړ�������\��
		/// </summary>
		/// <param name="role"> �{�[�h�̎�� </param>
		void hideBoard(const BoardRole& role);

	};
}