#include "HoleAccessObject.hpp"
#include "../EnemyAccessObject/RandomWalkingEnemyAccessObject/RandomWalkingEnemyAccessObject.hpp"
#include "../../../../../../Config/Config.hpp"


namespace Kokoha
{
	HoleAccessObject::HoleAccessObject(const Vec2& pos)
		: EnemyAccessObject(pos, U"HoleAccessObject")
	{
	}

	void HoleAccessObject::update(const Terrain& terrain)
	{
		EnemyAccessObject::update(terrain);
	}

	Vec2 HoleAccessObject::getTargetPos()
	{
		return body().center;
	}

	void HoleAccessObject::makeEnemy()
	{
		// 生成する敵数の制限
		static const size_t ENEMY_SIZE_LIMIT = Config::get<size_t>(U"HoleAccessObject.enemySizeLimit");
		if (m_enemyGuidList.size() >= ENEMY_SIZE_LIMIT) // TODO config
		{
			return;
		}

		// TODO 作成
		static const double ENEMY_MAKE_TIME = Config::get<double>(U"HoleAccessObject.enemyMakeTime");
		m_makingObjectTime += Scene::DeltaTime();
		if (m_makingObjectTime < ENEMY_MAKE_TIME)
		{
			return;
		}

		m_makingObjectTime = 0;
		Ptr ptr = std::make_shared<RandomWalkingEnemyAccessObject>(body().center);
		m_enemyGuidList.emplace_back(ptr->guid());
		makeObject(std::move(ptr));
	}

	void HoleAccessObject::checkOthers(const Terrain& terrain, const GuidToObject& guidToObject, const TypeToGuidSet& typeToGuidSet)
	{
		Erase_if(
			m_enemyGuidList,
			[&guidToObject](const String& guid) { return !guidToObject.count(guid); }
		);
		makeEnemy();

		EnemyAccessObject::checkOthers(terrain, guidToObject, typeToGuidSet);
	}

	// TODO 作成したオブジェクトが消えてないかチェック
}
