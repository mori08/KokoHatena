#pragma once


#include"../ShareData/BoardManager/BoardManager.hpp"


// シーンの名前
enum class SceneName
{
	TITLE,   // TitleScene
	LOAD,    // RecordLoadScene
	DESKTOP, // DesktopScene
};


// シーンで共有されるデータ

namespace Kokoha
{
	class SceneShareData
	{
	public:

		BoardManager board;

	};
}

// シーン管理クラス
using MyApp = SceneManager<SceneName, Kokoha::SceneShareData>;