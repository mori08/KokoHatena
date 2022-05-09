#pragma once


#include"../ShareData/RecordManager/RecordManager.hpp"


// �V�[���̖��O
enum class SceneName
{
	TITLE, // �^�C�g��
	LOAD,  // ���[�h
};


// �V�[���ŋ��L�����f�[�^

namespace Kokoha
{
	class ShareData
	{
	public:

		RecordManager record;

	};
}

// �V�[���Ǘ��N���X
using MyApp = SceneManager<SceneName, Kokoha::ShareData>;