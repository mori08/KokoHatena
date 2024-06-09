#include "LastPlayerAccessObject.hpp"
#include "../../MinionAccessObject/LastMinonAccessObject/LastMinionAccessObject.hpp"

/*
*	定数についてはノート11 2024/06/08
*/

namespace Kokoha
{
	LastPlayerAccessObject::LastPlayerAccessObject(const Vec2& pos, int32 powerUpLevel)
		: PlayerAccessObject(pos)
		, m_powerUpLevel(powerUpLevel)
	{
	}

	void LastPlayerAccessObject::makeLight(const GuidToObject& guidToObject, const TypeToGuidSet& typeToGuidSet)
	{
		if (m_powerUpLevel == 0)
		{
			PlayerAccessObject::makeLight(guidToObject, typeToGuidSet);
			return;
		}

		for (int32 i = 0; i < m_powerUpLevel / 2 + 1; ++i)
		{
			Ptr ptr = std::make_shared<LastMinionAccessObject>(body().center, m_powerUpLevel);
			const double minionLightArea = ptr->light().area();

			if (minionLightArea > m_lightArea)
			{
				break;
			}
			m_lightArea -= minionLightArea;
			makeObject(std::move(ptr));
		}
	}
}
