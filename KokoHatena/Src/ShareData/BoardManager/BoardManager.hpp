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

		// ボードのリスト
		std::list<Board> m_boardList;

	public:

		BoardManager();

	public:

		/// <summary>
		/// 更新
		/// </summary>
		void update();

		/// <summary>
		/// 描画
		/// </summary>
		void draw() const;
	};
}