#pragma once

#include <Siv3D.hpp>


// �V�[���̖��O
enum class SceneName
{
	TITLE,              // �^�C�g�����
	DESKTOP,            // �f�X�N�g�b�v���
	LOAD_RECORD,        // �e�L�X�g�t�@�C����ǂݍ����Record�𐶐�
	LOAD_BOARD,         // Record��ǂݍ����Board�𐶐�
	SAVE_RECORD,        // Record���e�L�X�g�t�@�C������������
	SELECT_LOAD_RECORD, // ���[�h����RecordSet��I��
	SELECT_SAVE_RECORD, // �Z�[�u����RecordSet��I��
};

// �������SceneName�ɕϊ�����A�z�z��
static const std::unordered_map<String, SceneName> SCENE_NAME_MAP
{
	{ U"title", SceneName::TITLE },
	{ U"selectSaveRecord", SceneName::SELECT_SAVE_RECORD }
};