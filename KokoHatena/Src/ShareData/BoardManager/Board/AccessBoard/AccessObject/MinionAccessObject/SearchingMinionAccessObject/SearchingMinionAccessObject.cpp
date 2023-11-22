#include "SearchingMinionAccessObject.hpp"

namespace Kokoha
{
	SearchingMinionAccessObject::SearchingMinionAccessObject(const Vec2& pos)
		: MinionAccessObject(pos)
	{
	}

	void SearchingMinionAccessObject::setGoal(const Terrain& terrain, const GuidToObject& guidToObject, const TypeToGuidSet& typeToGuidSet)
	{
		try
		{
			const auto& goalObj = getFrontObject(Type::GOAL, guidToObject, typeToGuidSet);

			if (light().contains(goalObj.body().center))
			{
				m_goal = goalObj.body().center;
				return;
			}
		}
		catch (Error)
		{			
		}

		if (!terrain.isWalkAble(m_goal)
			|| Terrain::toInteger(m_goal)==Terrain::toInteger(body().center))
		{
			m_goal = Terrain::toPixel(Random(0, Terrain::N - 1));
		}
	}
}
