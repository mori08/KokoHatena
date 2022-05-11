#pragma once


#include"../ShareData/RecordManager/RecordManager.hpp"


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
	class ShareData
	{
	public:

		RecordManager record;

	};
}

// シーン管理クラス
using MyApp = SceneManager<SceneName, Kokoha::ShareData>;