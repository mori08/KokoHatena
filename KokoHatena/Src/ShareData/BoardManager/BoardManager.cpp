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

	std::list<std::unique_ptr<Board>>::iterator BoardManager::findBoardItr(const Board::Role& role)
	{
		for (auto itr = m_boardList.begin(); itr != m_boardList.end(); ++itr)
		{
			if ((*itr)->role() == role) { return itr; }
		}
		return m_boardList.end();
	}

	void BoardManager::displayBoard(const Board::Role& role, const String& requestText)
	{
		// 先頭に移動させるイテレータ
		auto boardItr = findBoardItr(role);

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

		// 先頭のボードの状態に命令を出す
		m_boardList.front()->receiveRequest(requestText);
	}

	void BoardManager::hideBoard(const Board::Role& role)
	{
		// 末尾に移動させるイテレータ
		auto boardItr = findBoardItr(role);

		// ボードが見つからないときエラー
		if (boardItr == m_boardList.end())
		{
			throw Error(U"Faild to find Board");
		}

		// 最前面に移動
		auto boardPtr = std::move(*boardItr);
		m_boardList.erase(boardItr);
		m_boardList.emplace_back(std::move(boardPtr));

		// 末尾のボードの状態をIS_HIDINGに変更
		m_boardList.front()->hide();
	}
}