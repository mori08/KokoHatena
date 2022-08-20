#pragma once


#include"../ShareData/BoardManager/BoardManager.hpp"
#include"../ShareData/RecordSet/RecordSet.hpp"


// �V�[���̖��O
enum class SceneName
{
	TITLE,              // �^�C�g�����
	DESKTOP,            // �f�X�N�g�b�v���
	LOAD_RECORD,        // �e�L�X�g�t�@�C����ǂݍ����Record�𐶐�
	SELECT_LOAD_RECORD, // ���[�h����RecordSet��I��
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