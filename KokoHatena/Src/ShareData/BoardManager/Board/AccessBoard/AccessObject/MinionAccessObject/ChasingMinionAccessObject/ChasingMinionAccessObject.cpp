#include "ChasingMinionAccessObject.hpp"
#include "../../../../../../../Config/Config.hpp"

namespace Kokoha
{
	ChasingMinionAccessObject::ChasingMinionAccessObject(const Vec2& pos, const String& chasingGuid)
		: MinionAccessObject(pos, maxLightArea())
		, m_chasingGuid(chasingGuid)
	{
	}

	void ChasingMinionAccessObject::setGoal(const Terrain&, const GuidToObject& guidToObject, const TypeToGuidSet&)
	{
		try
		{
			const auto& obj = getObject(m_chasingGuid, guidToObject);
			m_goal = obj.body().center;
		}
		catch (Error)
		{
			eraseAndMakeTrack();
		}
	}

	double ChasingMinionAccessObject::maxLightArea() const
	{
		static const double rtn
			= Config::get<double>(U"MinionAccessObject.Chasing.area");
		return rtn;
	}
}
