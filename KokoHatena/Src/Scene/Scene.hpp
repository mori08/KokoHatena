#pragma once


#include"../ShareData/BoardManager/BoardManager.hpp"
#include"../ShareData/RecordSet/RecordSet.hpp"


// シーンの名前
enum class SceneName
{
	TITLE,              // タイトル画面
	DESKTOP,            // デスクトップ画面
	LOAD_RECORD,        // テキストファイルを読み込んでRecordを生成
	SELECT_LOAD_RECORD, // ロードするRecordSetを選択
};


// シーンで共有されるデータ

namespace Kokoha
{
	class SceneShareData
	{
	public:

		// ボードの管理
		BoardManager board;
		
		// セーブデータと対応するRecordSetのリスト
		std::list<RecordSet> recordSetList;

		// Boardに対応させたRecord
		RecordSet nowRecordSet;

	};
}

// シーン管理クラス
using MyApp = SceneManager<SceneName, Kokoha::SceneShareData>;