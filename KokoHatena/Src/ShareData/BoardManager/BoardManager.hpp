#pragma once
#include"Board/Board.hpp"
#include"../RecordManager/RecordManager.hpp"

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
		std::list<Board> m_boardList;

		// �{�[�h�Ԃł̖���
		Optional<Board::BoardRequest> m_boardRequest;

	public:

		BoardManager();

	public:

		/// <summary>
		/// Record����
		/// </summary>
		/// <param name="recordManager"></param>
		void load(RecordManager& recordManager);

		/// <summary>
		/// �X�V
		/// </summary>
		void update();

		/// <summary>
		/// �`��
		/// </summary>
		void draw() const;
	};
}