#include "LastEnemyAccessObject.hpp"
#include "../../../../../../../Config/Config.hpp"
#include "../../../../../../../MyLibrary/MyLibrary.hpp"

namespace Kokoha
{
	LastEnemyAccessObject::LastEnemyAccessObject(const Vec2& pos)
		: EnemyAccessObject(pos)
		, m_angleFromPlayer(Random(Math::TwoPi))
		, m_velocity(Vec2::Zero())
	{

	}

	void LastEnemyAccessObject::update(const Terrain& terrain)
	{
		walk(m_velocity, terrain);

		m_bodyTexture.update();
		m_faceTexture.update();
	}

	void LastEnemyAccessObject::checkOthers(const Terrain& terrain, const GuidToObject& guidToObject, const TypeToGuidSet& typeToGuidSet)
	{
		static const double RADIUS
			= Config::get<double>(U"LastEnemyAccessObject.radius");
		static const double SPEED
			= Config::get<double>(U"LastEnemyAccessObject.speed");
		static const double RATE
			= Config::get<double>(U"LastEnemyAccessObject.rate");
		static const double JUMP_RATE
			= Config::get<double>(U"LastEnemyAccessObject.jumpRate");

		m_angleFromPlayer += Scene::DeltaTime() * SPEED / RADIUS / 2;
		if (randomFrequency(JUMP_RATE))
		{
			m_angleFromPlayer += Math::Pi;
		}

		const auto& playerObj = getFrontObject(Type::PLAYER, guidToObject, typeToGuidSet);

		const Vec2 targetPos = playerObj.body().center + RADIUS * angleToVec(m_angleFromPlayer);
		const Vec2 direction = targetPos - body().center;
		const Vec2 target = direction.isZero()
			? direction
			: SPEED * direction.normalized();
		internalDividingPoint(m_velocity, target, RATE);

		EnemyAccessObject::checkOthers(terrain, guidToObject, typeToGuidSet);
	}
}
