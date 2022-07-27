#include"BoardManager.hpp"

namespace Kokoha
{
	BoardManager::BoardManager()
	{

	}

	void BoardManager::load(RecordManager&)
	{
		
	}

	void BoardManager::update()
	{
		// 先頭ボードの入力を受け付ける
		if (!m_boardList.empty())
		{
			const auto& boardRequest = m_boardList.front()->input();
		}

		// 表示中のボードの更新
		for (auto& board : m_boardList)
		{
			board->update();
		}
	}

	void BoardManager::draw() const
	{
		// 表示中のボードの描画
		for (const auto& board : m_boardList)
		{
			board->draw();
		}
	}

	void BoardManager::displayBoard(const Board::Role& role, const String& requestText)
	{
		// 先頭に移動させるイテレータ
		auto boardItr = m_boardList.end();

		// 指定したロールのボードのイテレータの探索
		for (auto itr = m_boardList.begin(); itr != m_boardList.end(); ++itr)
		{
			if ((*itr)->role() == role)
			{
				boardItr = itr; break;
			}
		}

		// ボードが見つからないときエラー
		if (boardItr == m_boardList.end())
		{
			throw Error(U"Faild to find Board");
		}

		// 最前面に移動
		auto boardPtr = std::move(*boardItr);
		m_boardList.erase(boardItr);
		m_boardList.emplace_front(std::move(boardPtr));

		// 先頭のボードの状態をIS_DISPLAYEDに変更
		m_boardList.front()->display();
	}
}