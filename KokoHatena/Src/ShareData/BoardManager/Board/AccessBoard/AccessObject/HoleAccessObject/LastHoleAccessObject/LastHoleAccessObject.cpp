#include "LastHoleAccessObject.hpp"
#include "../../../../../../../MyLibrary/MyLibrary.hpp"

namespace Kokoha
{
	LastHoleAccessObject::LastHoleAccessObject(const Vec2& pos, double angleFromGoal)
		: HoleAccessObject(pos)
		, m_angleFromGoal(angleFromGoal)
	{
	}

	void LastHoleAccessObject::update(const Terrain& terrain)
	{
		static const double RADIUS = Config::get<double>(U"LastHoleAccessObject.radius");
		static const double SPEED = Config::get<double>(U"LastHoleAccessObject.speed");

		m_angleFromGoal += Scene::DeltaTime() * SPEED / RADIUS;

		const Vec2 targetPos = m_goalPos + RADIUS * angleToVec(m_angleFromGoal);
		walkToGoal(SPEED, targetPos, terrain);
		HoleAccessObject::update(terrain);
	}

	void LastHoleAccessObject::checkOthers(const Terrain& terrain, const GuidToObject& guidToObject, const TypeToGuidSet& typeToGuidSet)
	{
		m_goalPos
			= getFrontObject(Type::GOAL, guidToObject, typeToGuidSet).body().center;

		HoleAccessObject::checkOthers(terrain, guidToObject, typeToGuidSet);
	}

	size_t LastHoleAccessObject::enemySizeLimit() const
	{
		static const size_t ENEMY_SIZE_LIMIT
			= Config::get<size_t>(U"LastHoleAccessObject.enemySizeLimit");
		return ENEMY_SIZE_LIMIT;
	}

	double LastHoleAccessObject::enemyMakeTime() const
	{
		static const double ENEMY_MAKE_TIME
			= Config::get<double>(U"LastHoleAccessObject.enemyMakeTime");
		return ENEMY_MAKE_TIME;
	}
}
