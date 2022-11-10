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
		// �I�u�W�F�N�g�ւ̓���
		for (const auto& object : m_objectMap)
		{
			object.second->input(cursorPosFInBoard());
		}
	}

	void AccessBoard::updateInBoard(BoardRequest&)
	{
		// �I�u�W�F�N�g�̐���
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

		// ���I�u�W�F�N�g�̏��̎擾
		for (const auto& object : m_objectMap)
		{
			object.second->checkOthers(m_terrain, m_objectMap, m_typeToGuidSet);
		}

		// �X�V
		for (const auto& object : m_objectMap)
		{
			object.second->update(m_terrain);
		}

		// �폜
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
		// �I�u�W�F�N�g�̏o�����̕`��
		for (const auto& object : m_objectMap)
		{
			object.second->drawLight();
		}

		m_terrain.draw();

		// �I�u�W�F�N�g�̕`��
		for (const auto& object : m_objectMap)
		{
			object.second->draw();
		}
	}
}