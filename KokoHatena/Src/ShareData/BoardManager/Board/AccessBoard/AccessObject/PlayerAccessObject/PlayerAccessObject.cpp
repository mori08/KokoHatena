#include "PlayerAccessObject.hpp"
#include "../LightAccessObject/LightAccessObject.hpp"
#include "../../../../../../MyLibrary/MyLibrary.hpp"
#include "../../../../../../Config/Config.hpp"

namespace Kokoha
{
	PlayerAccessObject::PlayerAccessObject(const Vec2& pos)
		: AccessObject(Type::PLAYER, pos)
		, m_movement(0, 0)
	{
		static const double LIGHT_ALPHA = Config::get<double>(U"PlayerAccessObject.lightAlpha");
		static const double LIGHT_DISTANCE = Config::get<double>(U"PlayerAccessObject.lightDistance");

		light()
			.setDistance(LIGHT_DISTANCE)
			.setAlpha(LIGHT_ALPHA);
	}

	void PlayerAccessObject::input(const Vec2&)
	{
		if (KeyW.pressed()) { m_movement += Vec2::Up();    }
		if (KeyS.pressed()) { m_movement += Vec2::Down();  }
		if (KeyA.pressed()) { m_movement += Vec2::Left();  }
		if (KeyD.pressed()) { m_movement += Vec2::Right(); }

		static const double SPEED = Config::get<double>(U"PlayerAccessObject.speed");
		m_movement *= SPEED;
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
		for (const String& guid : typeToGuidSet.find(Type::ENEMY)->second)
		{
			if (guidToObject.find(guid)->second->body().intersects(body()))
			{
				erase();
			}
		}
	}
}