#pragma once


#include"SceneName.hpp"
#include"../ShareData/BoardManager/BoardManager.hpp"
#include"../ShareData/RecordSet/RecordSet.hpp"


namespace Kokoha
{
	/// <summary>
	/// �V�[���ŋ��L�����f�[�^
	/// </summary>
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