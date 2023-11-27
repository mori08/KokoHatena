#include "TrackAccessObject.hpp"
#include "../../../../../../Config/Config.hpp"
#include "../../../../../../MyLibrary/MyLibrary.hpp"

namespace
{
	// 半径
	const double& radius()
	{
		static const double rtn = Kokoha::Config::get<double>(U"TrackAccessObject.radius");
		return rtn;
	}
}

namespace Kokoha
{
	TrackAccessObject::TrackAccessObject(const Vec2& pos, const Vec2& movement)
		: AccessObject(Type::TRACK, Circle(pos,radius()))
		, m_playerPos(pos)
		, m_movement(movement)
	{
		static const double LIGHT_ALPHA = Config::get<double>(U"TrackAccessObject.alpha");
		light()
			.setAlpha(LIGHT_ALPHA)
			.setDistance(radius())
			.setCentralAngle(Math::TwoPi)
			.setShadowMode(false)
			.on();
	}

	void TrackAccessObject::update(const Terrain& terrain)
	{
		static const double SPEED = Config::get<double>(U"TrackAccessObject.speed");

		double speed = m_movement.length();
		if (speed < 1e-2)
		{
			walkToGoal(SPEED, m_playerPos, terrain);
		}
		else
		{
			static const double SLOW_DOWN_RATE = Config::get<double>(U"TrackAccessObject.slowDownRate");
			internalDividingPoint(speed, 0, SLOW_DOWN_RATE);
			m_movement *= speed / m_movement.length();
			walk(m_movement, terrain);
		}

		light()
			.setSourcePos(body().center)
			.update(terrain);
	}

	void TrackAccessObject::checkOthers(const Terrain&, const GuidToObject& guidToObject, const TypeToGuidSet& typeToGuidSet)
	{
		try
		{
			const auto& player = getFrontObject(Type::PLAYER, guidToObject, typeToGuidSet);
			m_playerPos = player.body().center;

			if (player.body().intersects(body()))
			{
				erase();
			}
		}
		catch (Error)
		{
			m_playerPos = body().center;
		}
	}
}
