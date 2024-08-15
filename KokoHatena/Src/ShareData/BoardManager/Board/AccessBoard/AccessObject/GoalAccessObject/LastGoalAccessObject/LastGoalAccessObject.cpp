#include "LastGoalAccessObject.hpp"
#include "../../HoleAccessObject/LastHoleAccessObject/LastHoleAccessObject.hpp"
#include "../../../../../../../Config/Config.hpp"
#include "../../../../../../../MyLibrary/MyLibrary.hpp"

namespace Kokoha
{
	LastGoalAccessObject::LastGoalAccessObject(const Vec2& pos)
		: AccessObject(Type::GOAL, pos)
		, m_angle(-Math::HalfPi)
		, m_playerPos(pos)
	{
		for (int32 i = 0; i < 3; ++i)
		{
			makeObject(std::make_shared<LastHoleAccessObject>(pos, i * Math::OneThirdPi));
		}
	}

	void LastGoalAccessObject::update(const Terrain& terrain)
	{
		static const Vec2 CENTER_POS = Config::get<Vec2>(U"AccessBoard.size")/2;
		static const double RADIUS = Config::get<double>(U"LastGoalAccessObject.radius");
		static const double SPEED = Config::get<double>(U"LastGoalAccessObject.speed");

		const Vec2 toPlayer = m_playerPos - CENTER_POS;
		const Vec2 toGoal = body().center - CENTER_POS;

		if (toPlayer.isZero() || toGoal.isZero()) {}
		else
		{
			m_angle +=
				(twoVecToAngle(toPlayer, toGoal) > 0 ? +1 : -1)
				* Scene::DeltaTime()
				* SPEED / RADIUS
			;
		}

		const Vec2 targetPos = CENTER_POS + RADIUS * angleToVec(m_angle);
		walkToGoal(SPEED, targetPos, terrain);
	}

	void LastGoalAccessObject::draw() const
	{
		TextureAsset(U"LastGoalAccessObject").drawAt(body().center);
	}

	void LastGoalAccessObject::checkOthers(const Terrain& terrain, const GuidToObject& guidToObject, const TypeToGuidSet& typeToGuidSet)
	{
		m_playerPos = getFrontObject(Type::PLAYER, guidToObject, typeToGuidSet).body().center;
	}
}
