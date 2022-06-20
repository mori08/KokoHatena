#pragma once


#include"../ShareData/RecordManager/RecordManager.hpp"


// �V�[���̖��O
enum class SceneName
{
	TITLE,   // TitleScene
	LOAD,    // RecordLoadScene
	DESKTOP, // DesktopScene
};


// �V�[���ŋ��L�����f�[�^

namespace Kokoha
{
	class SceneShareData
	{
	public:

		RecordManager record;

	};
}

// �V�[���Ǘ��N���X
using MyApp = SceneManager<SceneName, Kokoha::SceneShareData>;