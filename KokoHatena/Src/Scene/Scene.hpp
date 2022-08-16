#pragma once


#include"../ShareData/BoardManager/BoardManager.hpp"
#include"../ShareData/RecordSet/RecordSet.hpp"


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

		// �{�[�h�̊Ǘ�
		BoardManager board;
		
		// �Z�[�u�f�[�^�ƑΉ�����RecordSet�̃��X�g
		std::list<RecordSet> recordSetList;

		// Board�ɑΉ�������Record
		RecordSet nowRecordSet;

	};
}

// �V�[���Ǘ��N���X
using MyApp = SceneManager<SceneName, Kokoha::SceneShareData>;