#pragma once


// シーンの名前
enum class SceneName
{
	TITLE,              // タイトル画面
	DESKTOP,            // デスクトップ画面
	LOAD_RECORD,        // テキストファイルを読み込んでRecordを生成
	LOAD_BOARD,         // Recordを読み込んでBoardを生成
	SAVE_RECORD,        // Recordをテキストファイルを書き込み
	SELECT_LOAD_RECORD, // ロードするRecordSetを選択
	SELECT_SAVE_RECORD, // セーブするRecordSetを選択
};