#pragma once
#include"Board/Board.hpp"

namespace Kokoha
{
	/// <summary>
	/// ボードの管理を行う
	/// loadSceneでの初期化
	/// DesktopSceneでの更新と描画
	/// </summary>
	class BoardManager
	{
	private:

		std::list<Board> m_boardList;

	public:

		BoardManager();

	};
}