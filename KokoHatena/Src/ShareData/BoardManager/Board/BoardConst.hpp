#pragma once

#include <Siv3D.hpp>
#include "../../../Scene/SceneName.hpp"

namespace Kokoha
{
	/// <summary>
	/// 種類（役割）
	/// </summary>
	enum class BoardRole
	{
		MESSAGE,  // メッセージ
		SECURITY, // セキュリティ
		ACCESS,   // アクセス（パズルアクション部分）
	};

	// 文字列をBoradRoleに変換する連想配列
	static const std::unordered_map<String, BoardRole> BOARD_ROLE_MAP
	{
		{ U"access"  , BoardRole::ACCESS },
		{ U"security", BoardRole::SECURITY },
		{ U"message" , BoardRole::MESSAGE }
	};

	/// <summary>
	/// 状態
	/// </summary>
	enum class BoardState
	{
		IS_DISPLAYED, // 表示中
		IS_HIDING,    // 非表示
		NONE,         // 利用不可
	};

	/// <summary>
	/// 外部へ送信するデータ
	/// </summary>
	class BoardRequest
	{
	public:

		// 他ボードへの命令
		std::list<std::pair<BoardRole, String>> toBoard;

		// Recordへの書き込み
		std::unordered_map<String, int32> toRecord;

		// Scene遷移
		Optional<SceneName> toScene = none;
	};

	// ↓別ファイルに移したい

	/// <summary>
	/// 他クラスにBoardの情報を渡す
	/// </summary>
	class BoardArg
	{
	private:

		// Boardの座標
		RectF m_boardRect;

	public:

		BoardArg(const Size& size)
			: m_boardRect(0, 0, size)
		{}

		/// <summary> Boardの座標の設定 </summary> 
		void setPos(const Vec2& pos);

		/// <summary> Boardの座標の取得 </summary> 
		Vec2 getPos() const
		{
			return m_boardRect.pos;
		}

		/// <summary>
		/// Board上でのカーソルの座標を取得
		/// </summary>
		/// <returns> Board上のカーソルの座標 </returns>
		Vec2 cursorPos() const;

		/// <summary>
		/// Boardの範囲の取得
		/// </summary>
		/// <returns> Boardの範囲 </returns>
		const RectF rect() const
		{
			return m_boardRect;
		}
	};
}
