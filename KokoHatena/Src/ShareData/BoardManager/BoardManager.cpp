#include"BoardManager.hpp"
#include"Board/MailBoard/MailBoard.hpp"
#include"Board/AccessBoard/AccessBoard.hpp"
#include"../../Config/Config.hpp"
#include"../../MyLibrary/MyLibrary.hpp"

namespace Kokoha
{
	BoardManager::BoardManager()
	{

	}

	void BoardManager::load(RecordManager&)
	{
		m_boardList.clear();

		m_boardList.emplace_back(std::make_unique<MailBoard>());
		m_boardList.emplace_back(std::make_unique<AccessBoard>());
	}

	void BoardManager::update()
	{
		// アイコンを押したときの処理
		for (auto itr = m_boardList.begin(); itr != m_boardList.end(); ++itr)
		{
			if (!(*itr)->onIconClicked()) { continue; }

			const bool isTop = (itr == m_boardList.begin() && (*itr)->state() == Board::State::IS_DISPLAYED);
			if (isTop) // ボードが先頭で表示中のとき
			{
				hideBoard((*itr)->role()); // 非表示にする
			}
			else // ボードが先頭にないとき
			{
				displayBoard((*itr)->role()); // 先頭に表示する
			}

			break;
		}

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
		Scene::Rect().draw(Palette::Gray);

		// 表示中のボードの描画
		for (auto itr = m_boardList.rbegin(); itr != m_boardList.rend(); ++itr)
		{
			(*itr)->draw();
		}

		// アイコンの描画
		static const int32 ICON_BAR_HEIGHT = Config::get<int32>(U"Board.iconSize.y");
		const Rect iconBar(0, Scene::Height() - ICON_BAR_HEIGHT, Scene::Width(), ICON_BAR_HEIGHT);
		iconBar.draw(MyBlack);
		iconBar.drawFrame(0, 2, MyWhite);
		for (const auto& board : m_boardList)
		{
			board->drawIcon();
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
		m_boardList.back()->hide();
	}
}