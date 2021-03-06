#pragma once


#include "../../BoardShareData/BoardShareData.hpp"


namespace Kokoha
{
	/// <summary>
	/// MessageBoardクラス
	/// Messageの表示
	/// </summary>
	class MessageBoard : public Board
	{
	private:

		// 表示するメッセージの名前
		Optional<String> m_messageName;

		// メッセージ用の設定ファイル
		const TOMLReader m_toml;

	public:

		MessageBoard(const Role& role);

	public:

		void inputInBoard(BoardShareData& shareData) override;

		void updateInBoard(BoardShareData& shareData) override;

		void drawInBoard(const BoardShareData& shareData) const override;

	private:

		/// <summary>
		/// メッセージを選ぶ画面での更新
		/// </summary>
		void updateSelectMessage(BoardShareData& shareData);

		/// <summary>
		/// メッセージを選ぶ画面での描画
		/// </summary>
		void drawSelectMessage() const;

		/// <summary>
		/// メッセージを読む画面での更新
		/// </summary>
		void updateReadMessage();

		/// <summary>
		/// メッセージを読む画面での描画
		/// </summary>
		void drawReadMessage()const;

	private:

		/// <summary>
		/// ロボットのメッセージを読むことができるか取得
		/// </summary>
		/// <returns> ロボットのメッセージを読むことができるとき true ,　そうでないとき false </returns>
		static bool readAbleRobotMessage();

	};
}