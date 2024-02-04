#include "RandomWalkingEnemyAccessObject.hpp"
#include "../../../../../../../Config/Config.hpp"

namespace Kokoha
{
	RandomWalkingEnemyAccessObject::RandomWalkingEnemyAccessObject(const Vec2& pos)
		: EnemyAccessObject(pos)
		, m_waitingSecond(0)
	{
		static const double SPEED = Config::get<double>(U"RandomWalkingEnemyAccessObject.speed");
		m_speed = SPEED;
	}

	void RandomWalkingEnemyAccessObject::update(const Terrain& terrain)
	{
		static const double WAITING_SECOND
			= Config::get<double>(U"RandomWalkingEnemyAccessObject.waitingSecond");
		static const double TARGET_POS_DIST
			= Config::get<double>(U"RandomWalkingEnemyAccessObject.targetPosDist");

		if (Terrain::toInteger(m_targetPos) == Terrain::toInteger(body().center))
		{
			m_waitingSecond += Scene::DeltaTime();
		}

		if (m_waitingSecond > WAITING_SECOND)
		{
			const Vec2 pos = Terrain::toPixel(Random(0, Terrain::N - 1));
			if (terrain.getDist(body().center, pos) < TARGET_POS_DIST)
			{
				m_waitingSecond = 0;
				m_targetPos = pos;
			}
		}

		EnemyAccessObject::update(terrain);
	}
}
