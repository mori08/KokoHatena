#pragma once
#include"Board/Board.hpp"
#include"../RecordManager/RecordManager.hpp"

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

		// ボード間での命令
		Optional<Board::BoardRequest> m_boardRequest;

	public:

		BoardManager();

	public:

		/// <summary>
		/// Recordから
		/// </summary>
		/// <param name="recordManager"></param>
		void load(RecordManager& recordManager);

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