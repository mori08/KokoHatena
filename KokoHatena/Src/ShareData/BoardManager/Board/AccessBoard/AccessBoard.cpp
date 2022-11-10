#include"AccessBoard.hpp"
#include"AccessObject/PlayerAccessObject/PlayerAccessObject.hpp"
#include"AccessObject/EnemyAccessObject/EnemyAccessObject.hpp"

namespace Kokoha
{
	AccessBoard::AccessBoard()
		: Board(BoardRole::ACCESS
			, U"AccessBoard"
			, BoardState::IS_HIDING
		)
		, m_terrain(U"asset/data/test.csv")
	{
		m_typeToGuidSet[AccessObject::Type::PLAYER] = {};
		m_typeToGuidSet[AccessObject::Type::ENEMY]  = {};
		m_typeToGuidSet[AccessObject::Type::LIGHT]  = {};
		m_typeToGuidSet[AccessObject::Type::GOAL]   = {};

		m_makeObjectList.emplace_back(std::make_unique<PlayerAccessObject>(Vec2(10, 10)));
		m_makeObjectList.emplace_back(std::make_unique<EnemyAccessObject>(Vec2(100, 100)));
	}

	void AccessBoard::receiveRequest(const String&)
	{
	}

	void AccessBoard::inputInBoard()
	{
		// オブジェクトへの入力
		for (const auto& object : m_objectMap)
		{
			object.second->input(cursorPosFInBoard());
		}
	}

	void AccessBoard::updateInBoard(BoardRequest&)
	{
		// オブジェクトの生成
		for (const auto& object : m_objectMap)
		{
			object.second->addObjectList(m_makeObjectList);
		}
		while (!m_makeObjectList.empty())
		{
			AccessObject::Ptr ptr = std::move(m_makeObjectList.front());
			
			m_typeToGuidSet[ptr->type()].insert(ptr->guid());
			m_objectMap.try_emplace(ptr->guid(), std::move(ptr));

			m_makeObjectList.pop_front();
		}

		// 他オブジェクトの情報の取得
		for (const auto& object : m_objectMap)
		{
			object.second->checkOthers(m_terrain, m_objectMap, m_typeToGuidSet);
		}

		// 更新
		for (const auto& object : m_objectMap)
		{
			object.second->update(m_terrain);
		}

		// 削除
		for (auto itr = m_objectMap.begin(); itr != m_objectMap.end();)
		{
			if (itr->second->isEraseAble())
			{
				m_typeToGuidSet[itr->second->type()].erase(itr->second->guid());
				itr = m_objectMap.erase(itr);
			}
			else { ++itr; }
		}
	}

	void AccessBoard::drawInBoard() const
	{
		// オブジェクトの出す光の描画
		for (const auto& object : m_objectMap)
		{
			object.second->drawLight();
		}

		m_terrain.draw();

		// オブジェクトの描画
		for (const auto& object : m_objectMap)
		{
			object.second->draw();
		}
	}
}