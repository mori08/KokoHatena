#include "DefencingEnemyAccessObject.hpp"
#include "../../../../../../../MyLibrary/MyLibrary.hpp"
#include "../../../../../../../Config/Config.hpp"

namespace Kokoha
{
	DefencingEnemyAccessObject::DefencingEnemyAccessObject(const Vec2& pos)
		: EnemyAccessObject(pos)
		, m_isChasing(false)
	{
		static const String TOML_KEY = U"DefencingEnemyAccessObject.VisualField";
		static const double ALPHA = Config::get<double>(TOML_KEY + U".alpha");
		static const double DISTANCE = Config::get<double>(TOML_KEY + U".distance");

		m_visualField
			.setColor(MyBlack)
			.setAlpha(ALPHA)
			.setCentralAngle(Math::TwoPi)
			.setDistance(DISTANCE)
			.setSourcePos(pos)
			.on();

		static const double SPEED
			= Config::get<double>(U"DefencingEnemyAccessObject.speed");
		m_speed = SPEED;
	}

	void DefencingEnemyAccessObject::update(const Terrain& terrain)
	{
		m_bodyTexture.update();
		m_faceTexture.update();

		m_visualField
			.setSourcePos(body().center)
			.update(terrain);

		EnemyAccessObject::update(terrain);
	}

	void DefencingEnemyAccessObject::draw() const
	{
		m_visualField.draw();
		EnemyAccessObject::draw();
	}

	void DefencingEnemyAccessObject::checkOthers(const Terrain& terrain, const GuidToObject& guidToObject, const TypeToGuidSet& typeToGuidSet)
	{
		EnemyAccessObject::checkOthers(terrain, guidToObject, typeToGuidSet);

		const auto& playerObj = getFrontObject(Type::PLAYER, guidToObject, typeToGuidSet);
		if (m_visualField.contains(playerObj.body().center))
		{
			m_faceTexture.startAnotherAnimation(U"chase");
			m_targetPos = playerObj.body().center;

			static const double CHASING_SPEED
				= Config::get<double>(U"DefencingEnemyAccessObject.chasingSpeed");
			m_speed = CHASING_SPEED;
			return;
		}

		if (Terrain::toInteger(m_targetPos) != Terrain::toInteger(body().center))
		{
			return;
		}

		static const double GOAL_DIST
			= Config::get<double>(U"DefencingEnemyAccessObject.goalDist");
		const auto& goalObj = getFrontObject(Type::GOAL, guidToObject, typeToGuidSet);
		const Vec2 pos = Terrain::toPixel(Random(0, Terrain::N - 1));
		if (terrain.getDist(goalObj.body().center, pos) < GOAL_DIST)
		{
			m_targetPos = pos;
			m_faceTexture.startAnotherAnimation(U"normal");

			static const double DEFENCING_SPEED
				= Config::get<double>(U"DefencingEnemyAccessObject.defencingSpeed");
			m_speed = DEFENCING_SPEED;
		}
	}
}
