#pragma once


#include"SceneName.hpp"
#include"../ShareData/BoardManager/BoardManager.hpp"
#include"../ShareData/RecordSet/RecordSet.hpp"


namespace Kokoha
{
	/// <summary>
	/// シーンで共有されるデータ
	/// </summary>
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
