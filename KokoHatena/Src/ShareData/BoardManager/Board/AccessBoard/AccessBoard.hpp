#pragma once
#include"../Board.hpp"
#include"AccessObject/AccessObject.hpp"
#include"Terrain/Terrain.hpp"

namespace Kokoha
{
	class AccessBoard : public Board
	{
	private:

		// �n�`
		Terrain m_terrain;

		// guid����I�u�W�F�N�g�ւ̘A�z�z��
		std::unordered_map<String, AccessObject::Ptr> m_objectMap;

		//  �I�u�W�F�N�g�̎�ނ���guid�ւ̘A�z�z��
		std::unordered_map<AccessObject::Type, std::list<String>> m_typeMap;

	public:

		AccessBoard();

	private:

		void receiveRequest(const String& requestText) override;

		void inputInBoard() override;

		void updateInBoard(BoardRequest& request) override;

		void drawInBoard() const override;

	};
}