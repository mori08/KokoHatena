#include"BoardManager.hpp"

namespace Kokoha
{
	BoardManager::BoardManager()
	{

	}

	void BoardManager::update()
	{
		// 先頭ボードの入力を受け付ける
		if (!m_boardList.empty())
		{
			m_boardList.front().input();
		}

		// 表示中のボードの更新
		for (auto& board : m_boardList)
		{
			board.update();
		}
	}

	void BoardManager::draw() const
	{
		// 表示中のボードの描画
		for (const auto& board : m_boardList)
		{
			board.draw();
		}
	}
}