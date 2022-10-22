#pragma once
#include"Board/Board.hpp"
#include"../RecordSet/RecordSet.hpp"
#include"../../Scene/SceneName.hpp"

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
		std::list<std::unique_ptr<Board>> m_boardList;

	public:

		BoardManager();

	public:

		/// <summary>
		/// Recordから
		/// </summary>
		/// <param name="recordSet"> セーブデータ </param>
		void load(const RecordSet& recordSet);

		/// <summary>
		/// 更新
		/// </summary>
		/// <param name="recordSet"> セーブデータ </param>
		Optional<SceneName> update(RecordSet& recordSet);

		/// <summary>
		/// 描画
		/// </summary>
		void draw() const;

	private:

		/// <summary>
		/// Board::Roleに対応したボードのイテレータを取得
		/// </summary>
		/// <param name="role"> ボードの種類 </param>
		std::list<std::unique_ptr<Board>>::iterator findBoardItr(const BoardRole& role);

		/// <summary>
		/// ボードを先頭に表示
		/// </summary>
		/// <param name="role"> ボードの種類 </param>
		/// <param name="requestText"> 開いたときrequestを投げる </param>
		void displayBoard(const BoardRole& role, const String& requestText = U"");

		/// <summary>
		/// ボードを末尾に移動させ非表示
		/// </summary>
		/// <param name="role"> ボードの種類 </param>
		void hideBoard(const BoardRole& role);

	};
}