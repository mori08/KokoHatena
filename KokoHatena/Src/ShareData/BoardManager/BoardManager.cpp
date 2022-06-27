#include"BoardManager.hpp"

namespace Kokoha
{
	BoardManager::BoardManager()
	{

	}

	void BoardManager::update()
	{
		// �擪�{�[�h�̓��͂��󂯕t����
		if (!m_boardList.empty())
		{
			m_boardList.front().input();
		}

		// �\�����̃{�[�h�̍X�V
		for (auto& board : m_boardList)
		{
			board.update();
		}
	}

	void BoardManager::draw() const
	{
		// �\�����̃{�[�h�̕`��
		for (const auto& board : m_boardList)
		{
			board.draw();
		}
	}
}