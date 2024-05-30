#include "SneakingEnemyAccessObject.hpp"
#include "../../../../../../../Config/Config.hpp"

namespace Kokoha
{
	SneakingEnemyAccessObject::SneakingEnemyAccessObject(const Vec2& pos)
		: EnemyAccessObject(pos)
		, m_waitingSecond(0)
	{
		static const double SPEED = Config::get<double>(U"SneakingEnemyAccessObject.speed");
		m_speed = SPEED;
	}

	void SneakingEnemyAccessObject::update(const Terrain& terrain)
	{
		if (Terrain::toInteger(m_targetPos) == Terrain::toInteger(body().center))
		{
			m_waitingSecond += Scene::DeltaTime();
		}

		EnemyAccessObject::update(terrain);
	}

	void SneakingEnemyAccessObject::checkOthers(const Terrain& terrain, const GuidToObject& guidToObject, const TypeToGuidSet& typeToGuidSet)
	{
		EnemyAccessObject::checkOthers(terrain, guidToObject, typeToGuidSet);

		static const double WAITING_SECOND
			= Config::get<double>(U"SneakingEnemyAccessObject.waitingSecond");
		static const double TARGET_POS_DIST
			= Config::get<double>(U"SneakingEnemyAccessObject.targetPosDist");
		static const double CHASE_RATE
			= Config::get<double>(U"SneakingEnemyAccessObject.chaseRate");

		if (m_waitingSecond < WAITING_SECOND) { return; }

		const Vec2& nextTargetPos =
			Random(1.0) < CHASE_RATE
			? getFrontObject(Type::PLAYER, guidToObject, typeToGuidSet).body().center
			: Terrain::toPixel(Random(0, Terrain::N - 1));

		if (terrain.getDist(body().center, nextTargetPos) > TARGET_POS_DIST)
		{
			return;
		}

		for (const String& guid : typeToGuidSet.find(Type::MINION)->second)
		{
			const Vec2 minionPos = getObject(guid, guidToObject).body().center;

			const double minionDist = terrain.getDist(minionPos, nextTargetPos);
			const double myDist = terrain.getDist(body().center, nextTargetPos);
			if (myDist > minionDist)
			{
				return;
			}
		}

		m_waitingSecond = 0;
		m_targetPos = nextTargetPos;
	}
}
