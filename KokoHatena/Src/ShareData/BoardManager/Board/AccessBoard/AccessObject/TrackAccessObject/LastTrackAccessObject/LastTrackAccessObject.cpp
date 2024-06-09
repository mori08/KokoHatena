#include "LastTrackAccessObject.hpp"
#include "../../../../../../../Config/Config.hpp"
#include "../../../../../../../MyLibrary/MyLibrary.hpp"

namespace Kokoha
{
	LastTrackAccessObject::LastTrackAccessObject(const Vec2& pos, const Vec2& movement, int32 powerUpLevel)
		: TrackAccessObject(pos, movement)
		, m_isChasingGoal(powerUpLevel >= 7)
	{

	}

	void LastTrackAccessObject::update(const Terrain& terrain)
	{
		walk(m_movement, terrain);

		light()
			.setSourcePos(body().center)
			.update(terrain);
	}

	void LastTrackAccessObject::checkOthers(const Terrain& terrain, const GuidToObject& guidToObject, const TypeToGuidSet& typeToGuidSet)
	{
		const auto& goal = getFrontObject(Type::GOAL, guidToObject, typeToGuidSet);
		const Vec2 goalPos = goal.body().center;

		if (body().intersects(goal.body()))
		{
			m_isChasingGoal = false;
		}

		TrackAccessObject::checkOthers(terrain, guidToObject, typeToGuidSet);

		const Vec2 targetPos = m_isChasingGoal
			? goalPos
			: m_playerPos
		;

		static const double RATE
			= Config::get<double>(U"TrackAccessObject.velocityRate");
		static const double SPEED
			= Config::get<double>(U"TrackAccessObject.highSpeed");
		const Vec2 direction = targetPos - body().center;
		const Vec2 target = direction.isZero()
			? direction
			: SPEED * direction.normalized();
		internalDividingPoint(m_movement, target, RATE);
	}
}
