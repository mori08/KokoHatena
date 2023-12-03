#include "ProtectingMinionAccessObject.hpp"
#include "../../../../../../../Config/Config.hpp"
#include "../../../../../../../MyLibrary/MyLibrary.hpp"

namespace Kokoha
{
	ProtectingMinionAccessObject::ProtectingMinionAccessObject(const Vec2& pos)
		: MinionAccessObject(pos, maxLightArea())
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
			|| Terrain::toInteger(m_goal) == Terrain::toInteger(body().center))
			{
				const Vec2 nextGoal = Terrain::toPixel(Random(0, Terrain::N - 1));
				if (terrain.getDist(playerObj.body().center, nextGoal) < PLAYER_DIST)
				{
					m_goal = nextGoal;
				}
			}
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
}
