#include "ChasingGoalAccessObject.hpp"
#include "../../../../../../../Config/Config.hpp"
#include "../../../../../../../MyLibrary/MyLibrary.hpp"

namespace Kokoha
{
	ChasingGoalAccessObject::ChasingGoalAccessObject(const Vec2& pos)
		: GoalAccessObject(pos)
		, m_targetPos(pos)
	{
		static const double LIGHT_ALPHA
			= Config::get<double>(U"ChasingGoalAccessObject.lightAlpha");
		light()
			.setColor(MyWhite)
			.setAlpha(LIGHT_ALPHA)
			.setSourcePos(pos)
			.setCentralAngle(Math::TwoPi)
			.on()
		;
	}

	void ChasingGoalAccessObject::update(const Terrain& terrain)
	{
		static const double SPEED
			= Config::get<double>(U"ChasingGoalAccessObject.speed");
		static const double LIGHT_RADIUS
			= Config::get<double>(U"ChasingGoalAccessObject.lightRadius");

		light()
			.setDistance(LIGHT_RADIUS, 0.01)
			.setSourcePos(body().center)
			.update(terrain);

		walkToGoal(SPEED, m_targetPos, terrain);

		GoalAccessObject::update(terrain);
	}

	void ChasingGoalAccessObject::checkOthers(const Terrain& terrain, const GuidToObject& guidToObject, const TypeToGuidSet& typeToGuidSet)
	{
		try
		{
			const auto& playerObj = getFrontObject(Type::PLAYER, guidToObject, typeToGuidSet);
			m_targetPos = playerObj.body().center;
		}
		catch (Error)
		{
		}
		GoalAccessObject::checkOthers(terrain, guidToObject, typeToGuidSet);
	}
}
