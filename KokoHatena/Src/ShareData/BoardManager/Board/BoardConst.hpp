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
		{ U"access"  , BoardRole::ACCESS }
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
}