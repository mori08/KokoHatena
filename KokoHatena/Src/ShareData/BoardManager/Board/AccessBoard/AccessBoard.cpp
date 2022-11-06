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
		m_makeObjectList.emplace_back(std::make_unique<EnemyAccessObject>(Vec2(10, 10)));
	}

	void AccessBoard::receiveRequest(const String&)
	{
	}

	void AccessBoard::inputInBoard()
	{
		// �I�u�W�F�N�g�ւ̓���
		for (const auto& object : m_objectMap)
		{
			object.second->input(cursorPosFInBoard());
		}
	}

	void AccessBoard::updateInBoard(BoardRequest&)
	{
		// ����
		while (!m_makeObjectList.empty())
		{
			AccessObject::Ptr ptr = std::move(m_makeObjectList.front());
			
			m_typeToGuidSet[ptr->type()].insert(ptr->guid());
			m_objectMap.try_emplace(ptr->guid(), std::move(ptr));

			m_makeObjectList.pop_front();
		}

		// �X�V
		for (const auto& object : m_objectMap)
		{
			object.second->update(m_terrain);

			// ���I�u�W�F�N�g�̏��̎擾
			object.second->checkOthers(m_terrain, m_objectMap, m_typeToGuidSet);
		}
	}

	void AccessBoard::drawInBoard() const
	{
		m_terrain.draw();

		for (const auto& object : m_objectMap)
		{
			object.second->draw();
		}
	}
}