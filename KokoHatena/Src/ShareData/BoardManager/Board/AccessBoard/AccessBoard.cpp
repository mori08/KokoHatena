#include"AccessBoard.hpp"
#include"AccessState/StartingAccessState/StartingAccessState.hpp"

namespace Kokoha
{
	AccessBoard::AccessBoard()
		: Board(BoardRole::ACCESS
			, U"AccessBoard"
			, BoardState::IS_HIDING
		)
		, m_stageName(U"test")
		, m_terrain(U"asset/data/stage/" + m_stageName + U".csv")
		, m_state(std::make_shared<StartingAccessState>(m_stageName))
	{
		m_typeToGuidSet[AccessObject::Type::PLAYER] = {};
		m_typeToGuidSet[AccessObject::Type::ENEMY]  = {};
		m_typeToGuidSet[AccessObject::Type::MINION] = {};
		m_typeToGuidSet[AccessObject::Type::GOAL]   = {};
	}

	void AccessBoard::receiveRequest(const String& requestText)
	{
	}

	void AccessBoard::inputInBoard()
	{
		m_state->input(cursorPosFInBoard());

		if (m_state->isUpdatingObject())
		{
			// �I�u�W�F�N�g�ւ̓���
			for (const auto& object : m_objectMap)
			{
				object.second->input(cursorPosFInBoard());
			}
		}
	}

	void AccessBoard::updateInBoard(BoardRequest& boradRequest)
	{
		if (auto stateOpt = m_state->update(m_objectMap, m_typeToGuidSet, boradRequest))
		{
			m_state = stateOpt.value();
		}

		if (m_state->isUpdatingObject())
		{
			// �I�u�W�F�N�g�̐���
			for (const auto& object : m_objectMap)
			{
				object.second->addObjectList(m_makeObjectList);
			}
			while (!m_makeObjectList.empty())
			{
				AccessObject::Ptr ptr = m_makeObjectList.front();

				m_typeToGuidSet[ptr->type()].insert(ptr->guid());
				m_objectMap.try_emplace(ptr->guid(), ptr);

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

		m_state->draw();
	}
}