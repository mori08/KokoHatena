#include"BoardManager.hpp"
#include"Board/MessageBoard/MessageBoard.hpp"
#include"Board/AccessBoard/AccessBoard.hpp"
#include"Board/SecurityBoard/SecurityBoard.hpp"
#include"Board/PowerBoard/PowerBoard.hpp"
#include"../../Config/Config.hpp"
#include"../../MyLibrary/MyLibrary.hpp"

namespace Kokoha
{
	BoardManager::BoardManager()
	{

	}

	void BoardManager::load(const RecordSet& recordSet)
	{
		m_boardList.clear();

		m_boardList.emplace_back(std::make_shared<MessageBoard>(recordSet));
		m_boardList.emplace_back(std::make_shared<AccessBoard>(recordSet));
		m_boardList.emplace_back(std::make_shared<SecurityBoard>(recordSet));
		m_boardList.emplace_back(std::make_shared<PowerBoard>());

		static const int32 LAST_DAY = Config::get<int32>(U"BoardManager.lastDay");
		m_isLastDay = recordSet.getRecord(U"Day") == LAST_DAY;
		m_time = 0;
	}

	Optional<SceneName> BoardManager::update(RecordSet& recordSet)
	{
		// アイコンを押したときの処理
		for (auto itr = m_boardList.begin(); itr != m_boardList.end(); ++itr)
		{
			if (!(*itr)->onIconClicked()) { continue; }

			const bool isTop = (itr == m_boardList.begin() && (*itr)->state() == BoardState::IS_DISPLAYED);
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

		// ボードをクリックしたとき先頭へ移動させる
		for (const auto& boardPtr: m_boardList)
		{
			if (!boardPtr->mouseLeftDown()) { continue; }

			displayBoard(boardPtr->role());

			break;
		}

		// 先頭ボードの入力を受け付ける
		if (true 
			&& !m_boardList.empty()
			&& m_boardList.front()->state() == BoardState::IS_DISPLAYED
			&& m_boardList.front()->input())
		{
			// inputの戻り値がtrueのときBoardを隠す
			hideBoard(m_boardList.front()->role());
		}

		// 表示中のボードの更新
		std::list<std::pair<BoardRole, String>> boardRequestList; // 他Boardへの命令のリスト
		for (auto& board : m_boardList)
		{
			BoardRequest request; // Boardから外部へのリクエスト
			board->update(request);

			// Board
			for (const auto& toBoard : request.toBoard)
			{
				boardRequestList.emplace_back(toBoard);
			}

			// Record
			for (const std::pair<String, int32>& record : request.toRecord) 
			{ 
				recordSet.setRecord(record.first, record.second); 
			}

			// Scene
			if (Optional<SceneName> sceneName = request.toScene) { return sceneName.value(); }
		}
		
		// 他ボードへの命令
		for (const std::pair<BoardRole, String>& boardRequest : boardRequestList)
		{
			if (boardRequest.second == U"hide")
			{
				hideBoard(boardRequest.first);
			}
			else
			{
				displayBoard(boardRequest.first, boardRequest.second);
			}
		}

		lastDay();

		return none;
	}

	void BoardManager::draw() const
	{
		// 背景の表示
		static const ColorF BACKGROUND_COLOR = Config::get<ColorF>(U"DesktopScene.backgroundColor");
		static const int32 LAST_DAY = Config::get<int32>(U"BoardManager.lastDay");

		if (m_isLastDay)
		{
			constexpr int32 CELL_SIZE = 20;
			Scene::Rect().draw(MyWhite);
			for (int32 x = 0; x < Scene::Width(); x += CELL_SIZE)
			{
				for (int32 y = 0; y < Scene::Height(); y += CELL_SIZE)
				{
					Point pos(x, y);
					if (randomFrequency(0.01))
					{
						pos.x += Random(-1, +1);
						pos.y += Random(-1, +1);
					}
					Rect(pos, CELL_SIZE).draw(BACKGROUND_COLOR);
				}
			}
		}
		else
		{
			Scene::Rect().draw(BACKGROUND_COLOR);
		}

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

	std::list<std::shared_ptr<Board>>::iterator BoardManager::findBoardItr(const BoardRole& role)
	{
		for (auto itr = m_boardList.begin(); itr != m_boardList.end(); ++itr)
		{
			if ((*itr)->role() == role) { return itr; }
		}

		throw Error(U"Faild to find Board");
	}

	void BoardManager::displayBoard(const BoardRole& role, const String& requestText)
	{
		// 先頭に移動させるイテレータ
		auto boardItr = findBoardItr(role);

		// ボードが見つからないときエラー
		if (boardItr == m_boardList.end())
		{
			throw Error(U"Faild to find Board");
		}

		// 最前面に移動
		auto boardPtr = *boardItr;
		m_boardList.erase(boardItr);
		m_boardList.emplace_front(boardPtr);

		// 先頭のボードの状態をIS_DISPLAYEDに変更
		m_boardList.front()->display();

		// 先頭のボードの状態に命令を出す
		m_boardList.front()->receiveRequest(requestText);
	}

	void BoardManager::hideBoard(const BoardRole& role)
	{
		// 末尾に移動させるイテレータ
		auto boardItr = findBoardItr(role);

		// ボードが見つからないときエラー
		if (boardItr == m_boardList.end())
		{
			throw Error(U"Faild to find Board");
		}

		// 最前面に移動
		auto boardPtr = *boardItr;
		m_boardList.erase(boardItr);
		m_boardList.emplace_back(boardPtr);

		// 末尾のボードの状態をIS_HIDINGに変更
		m_boardList.back()->hide();
	}

	void BoardManager::lastDay()
	{
		static const double SECURITY_TIME = Config::get<double>(U"BoardManager.securityTime");
		if (!m_isLastDay) { return; }
		m_time += Scene::DeltaTime();

		if (m_time > SECURITY_TIME)
		{
			m_time = 0;
			displayBoard(BoardRole::SECURITY, U"last");
		}
	}
}
