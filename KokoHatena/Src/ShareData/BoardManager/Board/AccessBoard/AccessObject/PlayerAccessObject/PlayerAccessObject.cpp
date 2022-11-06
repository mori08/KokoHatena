#include "PlayerAccessObject.hpp"
#include "../../../../../../MyLibrary/MyLibrary.hpp"
#include "../../../../../../Config/Config.hpp"

namespace Kokoha
{
	PlayerAccessObject::PlayerAccessObject(const Vec2& pos)
		: AccessObject(Type::PLAYER, pos)
		, m_movement(0, 0)
	{
	}

	void PlayerAccessObject::input(const Vec2&)
	{
		if (KeyW.pressed()) { m_movement += Vec2::Up();    }
		if (KeyS.pressed()) { m_movement += Vec2::Down();  }
		if (KeyA.pressed()) { m_movement += Vec2::Left();  }
		if (KeyD.pressed()) { m_movement += Vec2::Right(); }
	}

	void PlayerAccessObject::update(const Terrain& terrain)
	{
		static const double SPEED = Config::get<double>(U"PlayerAccessObject.speed");
		
		walk(SPEED * m_movement, terrain);

		m_movement = Vec2::Zero();
	}

	void PlayerAccessObject::draw() const
	{
		m_body.draw(MyBlack);
	}
}