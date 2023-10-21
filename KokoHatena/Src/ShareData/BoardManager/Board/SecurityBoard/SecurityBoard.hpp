#pragma once
#include "../Board.hpp"
#include "../../../RecordSet/RecordSet.hpp"

namespace Kokoha
{
	class SecurityBoard : public Board
	{
	private:

		// SecurityBoardで選択できる選択肢
		class Select
		{
		private:

			// ボタンの範囲
			Rect m_rect;

		public:

			// 選択肢として表示する文字列
			const String text;

			// 選択されたときにBoardへ送る命令
			const std::list<std::pair<BoardRole, String>> toBoard;

		public:

			/// @param t text
			/// @param b toBoard
			Select(const String& t, const std::list<std::pair<BoardRole, String>>& b)
				: text(t)
				, toBoard(b)
			{}

			/// <summary> ボタンの範囲の設定 </summary>
			/// <param name="center"> 中心座標 </param>
			void setRect(const Point& center);

			/// <summary> 描画 </summary>
			void draw() const;

			/// <summary> クリックされたか示す </summary>
			/// <param name="cursorPos"> カーソルの座標 </param>
			/// <returns> クリックされたとき true , そうでないとき false </returns>
			bool clicked(const Point& cursorPos) const;
		};

	private:

		// 中心する文字列
		String m_text;

		// 選択肢
		std::list<Select> m_selectList;

		// 他Boardへ送る命令
		Optional<BoardRequest> m_requestOpt;

	public:

		SecurityBoard(const RecordSet& recordSet);

	private:

		void receiveRequest(const String& requestText) override;

		void inputInBoard() override;

		void updateInBoard(BoardRequest& request) override;

		void drawInBoard() const override;

	private:

		/// <summary>
		/// 状態の変更
		/// </summary>
		/// <param name="stateName"> 状態名 (config.toml の SerucityBoard.<stateName> へ遷移 </param>
		void setState(const String& stateName);

	};
}
