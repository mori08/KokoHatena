#include "ChasingEnemyAccessObject.hpp"
#include "../../../../../../../MyLibrary/MyLibrary.hpp"
#include "../../../../../../../Config/Config.hpp"

namespace Kokoha
{
	ChasingEnemyAccessObject::ChasingEnemyAccessObject(const Vec2& pos)
		: EnemyAccessObject(pos)
		, m_initPos(pos)
		, m_playerPos(pos)
		, m_isChasing(false)
		, m_directionAngle(Random(0.0, Math::TwoPi))
		, m_lastTargetPos(pos)
	{
		static const String TOML_KEY = U"ChasingEnemyAccessObject.VisualField";
		static const double ALPHA = Config::get<double>(TOML_KEY + U".alpha");
		static const double CENTRAL_ANGLE = Config::get<double>(TOML_KEY + U".centralAngle");
		static const double DISTANCE = Config::get<double>(TOML_KEY + U".distance");

		m_visualField
			.setColor(MyBlack)
			.setAlpha(ALPHA)
			.setCentralAngle(CENTRAL_ANGLE)
			.setDistance(DISTANCE)
			.setDirectionAngle(m_directionAngle)
			.setSourcePos(pos)
			.on();
	}

	void ChasingEnemyAccessObject::update(const Terrain& terrain)
	{
		m_bodyTexture.update();
		m_faceTexture.update();

		if (m_isChasing)
		{
			chase(terrain);
		}
		else
		{
			patrol(terrain);
		}

		m_visualField
			.setDirectionAngle(m_directionAngle)
			.setSourcePos(body().center)
			.update(terrain);
	}

	void ChasingEnemyAccessObject::draw() const
	{
		m_visualField.draw();
		EnemyAccessObject::draw();
	}

	void ChasingEnemyAccessObject::checkOthers(const Terrain& terrain, const GuidToObject& guidToObject, const TypeToGuidSet& typeToGuidSet)
	{
		try
		{
			const auto& playerObj = getFrontObject(Type::PLAYER, guidToObject, typeToGuidSet);
			if (m_visualField.contains(playerObj.body().center))
			{
				m_isChasing = true;
				m_targetPos = playerObj.body().center;
			}
		}
		catch (Error)
		{

		}

		EnemyAccessObject::checkOthers(terrain, guidToObject, typeToGuidSet);
	}

	void ChasingEnemyAccessObject::chase(const Terrain& terrain)
	{
		static const double CHASE_SPEED
			= Config::get<double>(U"ChasingEnemyAccessObject.chaseSpeed");
		static const double ANGULAR_RATE
			= Config::get<double>(U"ChasingEnemyAccessObject.VisualField.angularRate");
		walkToGoal(CHASE_SPEED, m_targetPos, terrain);

		m_faceTexture.startAnotherAnimation(U"chase");

		if (!(m_targetPos - body().center).isZero())
		{
			const double targetAngle
				= nearestAngle(vecToAngle(m_targetPos - body().center), m_directionAngle);
			internalDividingPoint(m_directionAngle, targetAngle, ANGULAR_RATE);
		}

		if (body().center.distanceFrom(m_targetPos) < CHASE_SPEED * Scene::DeltaTime())
		{
			m_isChasing = false;
		}
	}

	void ChasingEnemyAccessObject::patrol(const Terrain& terrain)
	{
		static const double PATROL_SPEED
			= Config::get<double>(U"ChasingEnemyAccessObject.patrolSpeed");
		static const double PATROL_DIST
			= Config::get<double>(U"ChasingEnemyAccessObject.patrolDist");

		m_faceTexture.startAnotherAnimation(U"normal");

		if (Terrain::toInteger(m_targetPos) == Terrain::toInteger(body().center))
		{
			const Vec2 pos = Terrain::toPixel(Random(0, Terrain::N - 1));
			if (terrain.getDist(m_initPos, pos) < PATROL_DIST)
			{
				m_targetPos = pos;
			}
		}

		const Vec2 pathDirection = terrain.getPath(body().center, m_targetPos);
		updateDirection(pathDirection);
		walk(PATROL_SPEED * angleToVec(m_directionAngle), terrain);
	}

	void ChasingEnemyAccessObject::updateDirection(const Vec2& targetVec)
	{
		if (targetVec.isZero()) { return; }

		static const double ANGULAR_SPEED
			= Config::get<double>(U"ChasingEnemyAccessObject.VisualField.angularSpeed");
		const double targetAngle = nearestAngle(vecToAngle(targetVec), m_directionAngle);

		if (targetAngle - m_directionAngle > 0)
		{
			m_directionAngle = Min(
				targetAngle,
				m_directionAngle + ANGULAR_SPEED * Scene::DeltaTime()
			);
		}
		else
		{
			m_directionAngle = Max(
				targetAngle,
				m_directionAngle - ANGULAR_SPEED * Scene::DeltaTime()
			);
		}
	}
}
