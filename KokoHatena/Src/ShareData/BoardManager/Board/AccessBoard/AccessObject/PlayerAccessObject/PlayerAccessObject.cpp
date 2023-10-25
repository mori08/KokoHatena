#include "PlayerAccessObject.hpp"
#include "../../../../../../MyLibrary/MyLibrary.hpp"
#include "../../../../../../Config/Config.hpp"

namespace Kokoha
{
	PlayerAccessObject::PlayerAccessObject(const Vec2& pos)
		: AccessObject(Type::PLAYER, pos)
		, m_movement(0, 0)
		, m_lightMode(true)
		, m_direction(0)
	{
		static const double LIGHT_ALPHA = Config::get<double>(U"PlayerAccessObject.lightAlpha");

		light()
			.setAlpha(LIGHT_ALPHA)
			.setCentralAngle(Math::TwoPi)
			.on();
	}

	void PlayerAccessObject::input(const Vec2&)
	{
		if (KeyW.pressed()) { m_movement += Vec2::Up();    }
		if (KeyS.pressed()) { m_movement += Vec2::Down();  }
		if (KeyA.pressed()) { m_movement += Vec2::Left();  }
		if (KeyD.pressed()) { m_movement += Vec2::Right(); }

		// 速さ
		static const double SPEED = Config::get<double>(U"PlayerAccessObject.speed");
		m_movement *= SPEED;

		inputLight();
	}

	void PlayerAccessObject::update(const Terrain& terrain)
	{		
		walk(m_movement, terrain);

		m_movement = Vec2::Zero();

		light()
			.setSourcePos(body().center)
			.update(terrain);
	}

	void PlayerAccessObject::draw() const
	{
		body().draw(MyBlack);
	}

	void PlayerAccessObject::checkOthers(const Terrain&, const GuidToObject& guidToObject, const TypeToGuidSet& typeToGuidSet)
	{
	}

	void PlayerAccessObject::inputLight()
	{
		// 面積
		static const double AREA = Config::get<double>(U"PlayerAccessObject.lightArea");
		// 回転速度
		static const double SPIN_SPEED = Config::get<double>(U"PlayerAccessObject.lightSpinSpeed");

		// 距離の変更の比率
		static const double DISTANCE_RATE = Config::get<double>(U"AccessLight.Rate.distance");
		// 中心角の変更の比率
		static const double CENTRAL_ANGLE_RATE = Config::get<double>(U"AccessLight.Rate.centralAngle");
		// 光が射す角度の変更の比率
		static const double DIRECTION_ANGLE_RATE = Config::get<double>(U"AccessLight.Rate.directionAngle");

		m_lightMode ^= MouseR.down();

		if (m_lightMode)
		{
			light()
				.setDistance(Sqrt(2 * AREA / Math::TwoPi), DISTANCE_RATE)
				.setCentralAngle(Math::TwoPi, CENTRAL_ANGLE_RATE);
		}
		else
		{
			m_direction += Math::Pi * SPIN_SPEED * Mouse::Wheel();

			light()
				.setDistance(Sqrt(2 * AREA / Math::OneThirdPi), DISTANCE_RATE)
				.setCentralAngle(Math::OneThirdPi, CENTRAL_ANGLE_RATE)
				.setDirectionAngle(m_direction, DIRECTION_ANGLE_RATE);
		}
	}
}
