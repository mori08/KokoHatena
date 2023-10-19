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
		public:

			// 選択肢として表示する文字列
			String text;

			// 選択されたときにBoardへ送る命令
			std::list<std::pair<BoardRole, String>> toBoard;

		public:

			/// @param t text
			/// @param b toBoard
			Select(const String& t, std::list<std::pair<BoardRole, String>>& b)
				: text(t)
				, toBoard(b)
			{}
		};

	private:

		// 中心する文字列
		String m_text;

		// 選択肢
		std::list<Select> m_selectList;

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
