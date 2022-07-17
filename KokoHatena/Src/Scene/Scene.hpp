#pragma once


#include"../ShareData/RecordManager/RecordManager.hpp"
#include"../ShareData/BoardManager/BoardManager.hpp"


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
		BoardManager board;

	};
}

// �V�[���Ǘ��N���X
using MyApp = SceneManager<SceneName, Kokoha::SceneShareData>;