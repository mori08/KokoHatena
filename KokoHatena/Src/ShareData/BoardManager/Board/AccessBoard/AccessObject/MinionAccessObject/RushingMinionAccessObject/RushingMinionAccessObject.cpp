#include "RushingMinionAccessObject.hpp"
#include "../../../../../../../Config/Config.hpp"

namespace Kokoha
{
	RushingMinionAccessObject::RushingMinionAccessObject(const Vec2& pos, const Vec2& direction)
		: MinionAccessObject(pos, maxLightArea())
		, m_direction(direction.normalized())
	{
		m_erasingTime = Config::get<double>(U"MinionAccessObject.Rushing.erasingTime");
	}

	void RushingMinionAccessObject::setGoal(const Terrain&, const GuidToObject&, const TypeToGuidSet&)
	{
		m_erasingTime -= Scene::DeltaTime();
		
		if (m_erasingTime < 0)
		{
			eraseAndMakeTrack();
		}
	}

	double RushingMinionAccessObject::maxLightArea() const
	{
		static const double rtn
			= Config::get<double>(U"MinionAccessObject.Rushing.area");
		return rtn;
	}

	void RushingMinionAccessObject::walkMinion(const Terrain& terrain)
	{
		static const double SPEED = Config::get<double>(U"MinionAccessObject.speed");
		walk(SPEED * m_direction, terrain);
	}
}
