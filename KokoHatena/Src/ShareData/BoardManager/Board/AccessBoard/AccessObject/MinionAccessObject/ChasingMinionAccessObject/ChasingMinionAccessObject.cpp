#include "ChasingMinionAccessObject.hpp"

namespace Kokoha
{
	ChasingMinionAccessObject::ChasingMinionAccessObject(const Vec2& pos, const String& chasingGuid)
		: MinionAccessObject(pos)
		, m_chasingGuid(chasingGuid)
	{
	}

	void ChasingMinionAccessObject::setGoal(const Terrain& terrain, const GuidToObject& guidToObject, const TypeToGuidSet& typeToGuidSet)
	{
		try
		{
			const auto& obj = getObject(m_chasingGuid, guidToObject);
			m_goal = obj.body().center;
		}
		catch (Error)
		{

		}
	}
}
