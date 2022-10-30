#pragma once

#include <Siv3D.hpp>
#include "../../../Scene/SceneName.hpp"

namespace Kokoha
{
	/// <summary>
	/// ��ށi�����j
	/// </summary>
	enum class BoardRole
	{
		MESSAGE,  // ���b�Z�[�W
		SECURITY, // �Z�L�����e�B
		ACCESS,   // �A�N�Z�X�i�p�Y���A�N�V���������j
	};

	// �������BoradRole�ɕϊ�����A�z�z��
	static const std::unordered_map<String, BoardRole> BOARD_ROLE_MAP
	{
		{ U"access"  , BoardRole::ACCESS },
		{ U"security", BoardRole::SECURITY },
		{ U"access"  , BoardRole::ACCESS }
	};

	/// <summary>
	/// ���
	/// </summary>
	enum class BoardState
	{
		IS_DISPLAYED, // �\����
		IS_HIDING,    // ��\��
		NONE,         // ���p�s��
	};

	/// <summary>
	/// �O���֑��M����f�[�^
	/// </summary>
	class BoardRequest
	{
	public:

		// ���{�[�h�ւ̖���
		std::list<std::pair<BoardRole, String>> toBoard;

		// Record�ւ̏�������
		std::unordered_map<String, int32> toRecord;

		// Scene�J��
		Optional<SceneName> toScene = none;
	};
}