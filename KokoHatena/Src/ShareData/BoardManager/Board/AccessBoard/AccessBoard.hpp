#pragma once
#include"../Board.hpp"
#include"AccessObject/AccessObject.hpp"
#include"AccessState/AccessState.hpp"
#include"Terrain/Terrain.hpp"

namespace Kokoha
{
	class AccessBoard : public Board
	{
	private:

		// �X�e�[�W��
		const String m_stageName;

		// �n�`
		const Terrain m_terrain;

		// guid����I�u�W�F�N�g�ւ̘A�z�z��
		AccessObject::GuidToObject m_objectMap;

		//  �I�u�W�F�N�g�̎�ނ���guid�ւ̘A�z�z��
		AccessObject::TypeToGuidSet m_typeToGuidSet;

		std::shared_ptr<AccessState> m_state;

		// ��������I�u�W�F�N�g
		std::list<AccessObject::Ptr> m_makeObjectList;

	public:

		AccessBoard();

	private:

		void receiveRequest(const String& requestText) override;

		void inputInBoard() override;

		void updateInBoard(BoardRequest& request) override;

		void drawInBoard() const override;

	};
}