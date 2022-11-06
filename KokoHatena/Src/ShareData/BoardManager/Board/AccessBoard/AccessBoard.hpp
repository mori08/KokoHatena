#pragma once
#include"../Board.hpp"
#include"AccessObject/AccessObject.hpp"
#include"Terrain/Terrain.hpp"

namespace Kokoha
{
	class AccessBoard : public Board
	{
	private:

		// 地形
		Terrain m_terrain;

		// guidからオブジェクトへの連想配列
		std::unordered_map<String, AccessObject::Ptr> m_objectMap;

		//  オブジェクトの種類からguidへの連想配列
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