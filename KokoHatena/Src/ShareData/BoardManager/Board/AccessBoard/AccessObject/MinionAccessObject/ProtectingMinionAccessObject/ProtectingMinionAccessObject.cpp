#include "ProtectingMinionAccessObject.hpp"
#include "../../../../../../../Config/Config.hpp"
#include "../../../../../../../MyLibrary/MyLibrary.hpp"

namespace Kokoha
{
	ProtectingMinionAccessObject::ProtectingMinionAccessObject(const Vec2& pos)
		: MinionAccessObject(pos)
	{
		m_angle = Random(0.0, Math::TwoPi);
	}

	void ProtectingMinionAccessObject::setGoal(const Terrain& terrain, const GuidToObject& guidToObject, const TypeToGuidSet& typeToGuidSet)
	{
		static const double ANGLE_SPEED = Config::get<double>(U"MinionAccessObject.Protecting.angleSpeed");
		static const double DISTANCE = Config::get<double>(U"MinionAccessObject.Protecting.distance");
		m_angle += ANGLE_SPEED * Scene::DeltaTime();

		try
		{
			const auto& playerObj = getFrontObject(Type::PLAYER, guidToObject, typeToGuidSet);

			m_goal
				= playerObj.body().center
				+ DISTANCE * angleToVec(m_angle);
		}
		catch (Error)
		{

		}

	}
}
