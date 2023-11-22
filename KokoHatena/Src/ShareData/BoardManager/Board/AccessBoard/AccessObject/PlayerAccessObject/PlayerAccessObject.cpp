#include "PlayerAccessObject.hpp"
#include "../MinionAccessObject/SearchingMinionAccessObject/SearchingMinionAccessObject.hpp"
#include "../MinionAccessObject/ProtectingMinionAccessObject/ProtectingMinionAccessObject.hpp"
#include "../../../../../../MyLibrary/MyLibrary.hpp"
#include "../../../../../../Config/Config.hpp"

namespace Kokoha
{
	PlayerAccessObject::PlayerAccessObject(const Vec2& pos)
		: AccessObject(Type::PLAYER, pos)
		, m_movement(0, 0)
	{
		static const double LIGHT_ALPHA = Config::get<double>(U"PlayerAccessObject.lightAlpha");
		static const double LIGHT_AREA = Config::get<double>(U"PlayerAccessObject.lightArea");

		m_lightArea = LIGHT_AREA;

		light()
			.setAlpha(LIGHT_ALPHA)
			.setCentralAngle(Math::TwoPi)
			.on();
	}

	void PlayerAccessObject::input(const BoardArg& board)
	{
		if (KeyW.pressed()) { m_movement += Vec2::Up();    }
		if (KeyS.pressed()) { m_movement += Vec2::Down();  }
		if (KeyA.pressed()) { m_movement += Vec2::Left();  }
		if (KeyD.pressed()) { m_movement += Vec2::Right(); }

		// 速さ
		static const double SPEED = Config::get<double>(U"PlayerAccessObject.speed");
		m_movement *= SPEED;

		if (board.rect().leftClicked())
		{
			Ptr ptr = std::make_shared<ProtectingMinionAccessObject>(body().center);

			const double minionLightArea = ptr->light().area();

			if (minionLightArea < m_lightArea)
			{
				m_lightArea -= minionLightArea;
				makeObject(std::move(ptr));
			}
		}
	}

	void PlayerAccessObject::update(const Terrain& terrain)
	{		
		walk(m_movement, terrain);

		m_movement = Vec2::Zero();

		// 距離の変更の比率
		static const double DISTANCE_RATE = Config::get<double>(U"AccessLight.Rate.distance");

		// 面積から光の半径を計算
		const double lightDistance = Sqrt(2 * m_lightArea / Math::TwoPi);

		light()
			.setSourcePos(body().center)
			.setDistance(lightDistance, DISTANCE_RATE)
			.update(terrain);
	}

	void PlayerAccessObject::draw() const
	{
		body().draw(MyBlack);
	}

	void PlayerAccessObject::checkOthers(const Terrain&, const GuidToObject& guidToObject, const TypeToGuidSet& typeToGuidSet)
	{
		static const double LIGHT_AREA = Config::get<double>(U"PlayerAccessObject.lightArea");

		// 光が少しずつ削られてもとの値にならない
		// 少し追加で増やす
		static const double LIGHT_PLUS_RATE = Config::get<double>(U"PlayerAccessObject.lightPlusRate");

		// 光を吸収
		for (const auto& guid : typeToGuidSet.find(Type::TRACK)->second)
		{
			const auto& track = getObject(guid, guidToObject);

			if (track.body().intersects(body()))
			{
				m_lightArea += LIGHT_PLUS_RATE * track.constLight().area();
				m_lightArea = Min(m_lightArea, LIGHT_AREA);
			}
		}
	}
}
