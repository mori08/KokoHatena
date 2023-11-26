#include "SearchingMinionAccessObject.hpp"
#include "../../../../../../../Config/Config.hpp"

namespace Kokoha
{
	SearchingMinionAccessObject::SearchingMinionAccessObject(const Vec2& pos)
		: MinionAccessObject(pos, maxLightArea())
	{
	}

	void SearchingMinionAccessObject::setGoal(const Terrain& terrain, const GuidToObject& guidToObject, const TypeToGuidSet& typeToGuidSet)
	{
		if (!terrain.isWalkAble(m_goal)
			|| Terrain::toInteger(m_goal)==Terrain::toInteger(body().center))
		{
			m_goal = Terrain::toPixel(Random(0, Terrain::N - 1));
		}
	}

	double SearchingMinionAccessObject::maxLightArea() const
	{
		static const double rtn
			= Config::get<double>(U"MinionAccessObject.Searching.area");
		return rtn;
	}
}
