#include"AccessBoard.hpp"
#include"AccessState/StartingAccessState/StartingAccessState.hpp"
#include "AccessObject/PlayerAccessObject/PlayerAccessObject.hpp"
#include "AccessObject/EnemyAccessObject/EnemyAccessObject.hpp"
#include "AccessObject/EnemyAccessObject/RandomWalkingEnemyAccessObject/RandomWalkingEnemyAccessObject.hpp"
#include "AccessObject/EnemyAccessObject/ChasingEnemyAccessObject/ChasingEnemyAccessObject.hpp"
#include "AccessObject/GoalAccessObject/GoalAccessObject.hpp"

namespace
{
	// オブジェクト作成用の関数マップ作成用
	template<typename Type>
	std::pair<String, std::function<Kokoha::AccessObject::Ptr(const Vec2& pos)>> makeObjSet(const String& key)
	{
		return {
			key,
			[](const Vec2& pos)
			{
				return std::make_shared<Type>(pos);
			}
		};
	}
}

namespace Kokoha
{
	AccessBoard::AccessBoard(const RecordSet& recordSet)
		: Board(BoardRole::ACCESS
			, U"AccessBoard"
			, recordSet.getRecord(U"Day") == 0 ? BoardState::NONE : BoardState::IS_HIDING
		)
		, m_stageName(U"day" + ToString(recordSet.getRecord(U"Day")))
		, m_terrain(U"asset/data/stage/" + m_stageName + U".csv")
		, m_state(std::make_shared<StartingAccessState>(m_stageName))
	{
		m_typeToGuidSet[AccessObject::Type::PLAYER] = {};
		m_typeToGuidSet[AccessObject::Type::ENEMY]  = {};
		m_typeToGuidSet[AccessObject::Type::MINION] = {};
		m_typeToGuidSet[AccessObject::Type::TRACK]  = {};
		m_typeToGuidSet[AccessObject::Type::GOAL]   = {};
	}

	void AccessBoard::receiveRequest(const String& requestText)
	{
	}

	void AccessBoard::inputInBoard()
	{
		m_state->input(boardArg());

		if (m_state->isUpdatingObject())
		{
			// オブジェクトへの入力
			for (const auto& object : m_objectMap)
			{
				object.second->input(boardArg());
			}
		}
	}

	void AccessBoard::updateInBoard(BoardRequest& boradRequest)
	{
		if (m_state->isInitializingObject())
		{
			initObjectMap();
		}

		if (auto stateOpt = m_state->update(m_objectMap, m_typeToGuidSet, boradRequest))
		{
			m_state = stateOpt.value();
		}

		if (m_state->isUpdatingObject())
		{
			// オブジェクトの生成
			while (!m_makeObjectList.empty())
			{
				AccessObject::setMakingObject(
					m_makeObjectList.front(),
					m_objectMap,
					m_typeToGuidSet
				);

				m_makeObjectList.pop_front();
			}

			// 更新
			for (const auto& object : m_objectMap)
			{
				object.second->update(m_terrain);
			}

			// 他オブジェクトの情報の取得
			for (const auto& object : m_objectMap)
			{
				object.second->checkOthers(m_terrain, m_objectMap, m_typeToGuidSet);
			}

			for (const auto& object : m_objectMap)
			{
				object.second->addObjectList(m_makeObjectList);
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

		m_state->draw();
	}

	void AccessBoard::initObjectMap()
	{
		// オブジェクトの作成用のマップ
		static std::unordered_map<String, std::function<AccessObject::Ptr(const Vec2& pos)>> makeObjectMap =
		{
			makeObjSet<PlayerAccessObject>(U"player"),

			makeObjSet<EnemyAccessObject>             (U"enemy"),
			makeObjSet<RandomWalkingEnemyAccessObject>(U"enemy_randomWalking"),
			makeObjSet<ChasingEnemyAccessObject>      (U"enemy_chasing"),

			makeObjSet<GoalAccessObject>(U"goal")
		};

		// オブジェクト情報のclear
		m_objectMap.clear();
		for (auto& guidSet : m_typeToGuidSet)
		{
			guidSet.second.clear();
		}
		m_makeObjectList.clear();

		// オブジェクトの読み込み
		const TOMLReader objectToml(U"asset/data/stage/object.toml");
		for (const auto object : objectToml[m_stageName].tableArrayView())
		{
			const String type = object[U"type"].getString();
			const String marker = object[U"marker"].getString();
			const Vec2 pos = m_terrain.getMarker(marker);

			if (!makeObjectMap.count(type))
			{
				throw Error(U"Faild to make [" + type + U"] object");
			}

			AccessObject::setMakingObject(
				makeObjectMap[type](pos),
				m_objectMap,
				m_typeToGuidSet
			);
		}
	}
}
