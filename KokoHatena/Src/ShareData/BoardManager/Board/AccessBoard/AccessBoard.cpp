#include"AccessBoard.hpp"
#include"AccessObject/PlayerAccessObject/PlayerAccessObject.hpp"
#include"AccessObject/MinionAccessObject/MinionAccessObject.hpp"
#include"AccessObject/EnemyAccessObject/EnemyAccessObject.hpp"

namespace Kokoha
{
	AccessBoard::AccessBoard()
		: Board(BoardRole::ACCESS
			, U"AccessBoard"
			, BoardState::IS_HIDING
		)
		, m_stageName(U"test")
		, m_terrain(U"asset/data/stage/" + m_stageName + U".csv")
	{
		m_typeToGuidSet[AccessObject::Type::PLAYER] = {};
		m_typeToGuidSet[AccessObject::Type::ENEMY]  = {};
		m_typeToGuidSet[AccessObject::Type::MINION] = {};
		m_typeToGuidSet[AccessObject::Type::GOAL]   = {};

		// �I�u�W�F�N�g�̍쐬�p�̃}�b�v
		static std::unordered_map<String, std::function<AccessObject::Ptr(const Vec2& pos)>> makeObjectMap =
		{
			{U"player",[](const Vec2& pos) { return std::make_shared<PlayerAccessObject>(pos); }}
		};

		// �I�u�W�F�N�g�̓ǂݍ���
		const TOMLReader objectToml(U"asset/data/stage/object.toml");
		for (const auto object : objectToml[m_stageName].tableArrayView())
		{
			const String type = object[U"type"].getString();
			const Vec2   pos  = Terrain::toPixel(Point(object[U"x"].get<int32>(), object[U"y"].get<int32>()));

			m_makeObjectList.emplace_back(makeObjectMap[type](pos));
		}
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