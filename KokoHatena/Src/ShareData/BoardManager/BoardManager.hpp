#pragma once
#include"Board/Board.hpp"

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

		std::list<Board> m_boardList;

	public:

		BoardManager();

	};
}