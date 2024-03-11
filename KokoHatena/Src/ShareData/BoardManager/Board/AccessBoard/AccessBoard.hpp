#pragma once
#include"../Board.hpp"
#include"AccessObject/AccessObject.hpp"
#include"AccessState/AccessState.hpp"
#include"Terrain/Terrain.hpp"
#include"../../../RecordSet/RecordSet.hpp"

namespace Kokoha
{
	class AccessBoard : public Board
	{
	private:

		// ステージ名
		const String m_stageName;

		// 地形
		const Terrain m_terrain;

		// guidからオブジェクトへの連想配列
		AccessObject::GuidToObject m_objectMap;

		//  オブジェクトの種類からguidへの連想配列
		AccessObject::TypeToGuidSet m_typeToGuidSet;

		std::shared_ptr<AccessState> m_state;

		// 生成するオブジェクト
		std::list<AccessObject::Ptr> m_makeObjectList;

	public:

		AccessBoard(const RecordSet& recordSet);

	private:

		void receiveRequest(const String& requestText) override;

		void inputInBoard() override;

		void updateInBoard(BoardRequest& request) override;

		void drawInBoard() const override;

	private:

		void initObjectMap();

	};
}
