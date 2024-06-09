#include "LastMinionAccessObject.hpp"
#include "../../TrackAccessObject/LastTrackAccessObject/LastTrackAccessObject.hpp"
#include "../../../../../../../Config/Config.hpp"
#include "../../../../../../../MyLibrary/MyLibrary.hpp"

namespace Kokoha
{
	LastMinionAccessObject::LastMinionAccessObject(const Vec2& pos, int32 powerUpLevel)
		: MinionAccessObject(pos, maxLightAreaFromLevel(powerUpLevel))
		, m_powerUpLevel(powerUpLevel)
	{
		static const double SPEED
			= Config::get<double>(U"MinionAccessObject.Last.speed");
		m_velocity = SPEED * angleToVec(Random(Math::TwoPi));
	}

	void LastMinionAccessObject::setGoal(const Terrain& terrain, const GuidToObject& guidToObject, const TypeToGuidSet& typeToGuidSet)
	{
		double minDist = Inf<double>;
		m_goal = getFrontObject(Type::PLAYER, guidToObject, typeToGuidSet).body().center;

		for (const String& guid : typeToGuidSet.find(Type::ENEMY)->second)
		{
			const Vec2 enemyPos = guidToObject.find(guid)->second->body().center;
			const double dist = terrain.getDist(body().center, enemyPos);

			if (dist < minDist)
			{
				minDist = dist;
				m_goal = enemyPos;
			}
		}

		static const double SPEED
			= Config::get<double>(U"MinionAccessObject.Last.speed");
		static const double HIGH_SPEED
			= Config::get<double>(U"MinionAccessObject.Last.highSpeed");

		const double max_speed = m_powerUpLevel >= 9
			? HIGH_SPEED
			: SPEED
		;

		static const double VELOCITY_RATE
			= Config::get<double>(U"MinionAccessObject.Last.velocityRate");
		const Vec2 targetVelocity = max_speed * (m_goal - body().center).normalized();
		internalDividingPoint(m_velocity, targetVelocity, VELOCITY_RATE);
	}

	double LastMinionAccessObject::maxLightAreaFromLevel(int32 powerUpLevel) const
	{
		if (powerUpLevel >= 5)
		{
			static const double SMALL_AREA
				= Config::get<double>(U"MinionAccessObject.Last.smallArea");
			return SMALL_AREA;
		}

		static const double AREA
			= Config::get<double>(U"MinionAccessObject.Last.area");
		return AREA;
	}

	double LastMinionAccessObject::maxLightArea() const
	{
		return maxLightAreaFromLevel(m_powerUpLevel);
	}

	void LastMinionAccessObject::walkMinion(const Terrain& terrain)
	{
		walk(m_velocity, terrain);
	}

	void LastMinionAccessObject::makeTrack(const Vec2& movement)
	{
		if (m_powerUpLevel >= 3)
		{
			Ptr trackObjPtr = std::make_shared<LastTrackAccessObject>(body().center, movement, m_powerUpLevel);
			m_lightArea -= trackObjPtr->light().area();
			makeObject(std::move(trackObjPtr));
		}
		else
		{
			MinionAccessObject::makeTrack(movement);
		}
	}
}

