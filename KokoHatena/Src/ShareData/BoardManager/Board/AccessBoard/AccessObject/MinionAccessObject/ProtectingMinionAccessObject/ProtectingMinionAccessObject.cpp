#include "ProtectingMinionAccessObject.hpp"
#include "../../../../../../../Config/Config.hpp"
#include "../../../../../../../MyLibrary/MyLibrary.hpp"

namespace Kokoha
{
	ProtectingMinionAccessObject::ProtectingMinionAccessObject(const Vec2& pos)
		: MinionAccessObject(pos, maxLightArea())
		, m_speed(0)
	{
	}

	void ProtectingMinionAccessObject::setGoal(const Terrain& terrain, const GuidToObject& guidToObject, const TypeToGuidSet& typeToGuidSet)
	{
		static const double PLAYER_DIST
			= Config::get<double>(U"MinionAccessObject.Protecting.playerDist");

		try
		{
			const auto& playerObj = getFrontObject(Type::PLAYER, guidToObject, typeToGuidSet);

			if (!terrain.isWalkAble(m_goal)
			|| Terrain::toInteger(m_goal) == Terrain::toInteger(body().center)
			|| terrain.getDist(playerObj.body().center, m_goal) > PLAYER_DIST)
			{
				const Vec2 nextGoal = Terrain::toPixel(Random(0, Terrain::N - 1));
				if (terrain.getDist(playerObj.body().center, nextGoal) < PLAYER_DIST)
				{
					m_goal = nextGoal;
				}
			}

			static const double PLAYER_DIST
				= Config::get<double>(U"MinionAccessObject.Protecting.playerDist");
			static const double HIGH_SPEED
				= Config::get<double>(U"MinionAccessObject.Protecting.highSpeed");
			static const double SPEED_CHANGE_RATE
				= Config::get<double>(U"MinionAccessObject.Protecting.speedChangeRate");
			static const double SPEED = Config::get<double>(U"MinionAccessObject.speed");

			internalDividingPoint(
				m_speed,
				terrain.getDist(body().center, playerObj.body().center) > PLAYER_DIST
					? HIGH_SPEED
					: SPEED,
				SPEED_CHANGE_RATE
			);
		}
		catch (Error)
		{
			
		}

	}

	double ProtectingMinionAccessObject::maxLightArea() const
	{
		static const double rtn
			= Config::get<double>(U"MinionAccessObject.Protecting.area");
		return rtn;
	}

	void ProtectingMinionAccessObject::walkMinion(const Terrain& terrain)
	{
		walkToGoal(m_speed, m_goal, terrain);
	}
}
