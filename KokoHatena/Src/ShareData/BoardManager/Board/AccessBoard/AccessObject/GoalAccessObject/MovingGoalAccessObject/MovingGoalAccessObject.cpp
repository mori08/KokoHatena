#include "MovingGoalAccessObject.hpp"
#include "../../../../../../../Config/Config.hpp"

namespace Kokoha
{
	MovingGoalAccessObject::MovingGoalAccessObject(const Vec2& pos)
		: GoalAccessObject(pos)
		, m_targetPos(pos)
		, m_waitingSecond(0)
	{
	}

	void MovingGoalAccessObject::update(const Terrain& terrain)
	{
		static const double MAX_WAITING_SECOND
			= Config::get<double>(U"MovingGoalAccessObject.maxWaitingSecond");
		static const double TARGET_POS_DIST
			= Config::get<double>(U"MovingGoalAccessObject.targetPosDist");
		static const double WALKING_SPEED
			= Config::get<double>(U"MovingGoalAccessObject.speed");

		if (Terrain::toInteger(m_targetPos) == Terrain::toInteger(body().center))
		{
			m_waitingSecond += Scene::DeltaTime();
		}

		if (m_waitingSecond > MAX_WAITING_SECOND)
		{
			const Vec2 pos = Terrain::toPixel(Random(0, Terrain::N - 1));
			if (terrain.getDist(body().center, pos) < TARGET_POS_DIST)
			{
				m_waitingSecond = 0;
				m_targetPos = pos;
			}
		}

		walkToGoal(WALKING_SPEED, m_targetPos, terrain);
	}
}
