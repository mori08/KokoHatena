#include "PlayerAccessObject.hpp"
#include "../MinionAccessObject/SearchingMinionAccessObject/SearchingMinionAccessObject.hpp"
#include "../MinionAccessObject/ProtectingMinionAccessObject/ProtectingMinionAccessObject.hpp"
#include "../MinionAccessObject/ChasingMinionAccessObject/ChasingMinionAccessObject.hpp"
#include "../TrackAccessObject/TrackAccessObject.hpp"
#include "../../../../../../MyLibrary/MyLibrary.hpp"
#include "../../../../../../Config/Config.hpp"

namespace Kokoha
{
	PlayerAccessObject::PlayerAccessObject(const Vec2& pos)
		: AccessObject(Type::PLAYER, pos)
		, m_movement(0, 0)
		, m_makingLightPos(none)
		, m_trackTime(0)
		, m_trackPtr(none)
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
		static const double SLOW_SPEED = Config::get<double>(U"PlayerAccessObject.slowSpeed");
		static const double FAST_SPEED = Config::get<double>(U"PlayerAccessObject.fastSpeed");

		m_trackTime -= Scene::DeltaTime();
		if (m_trackTime < 0 && m_trackPtr)
		{
			makeObject(std::move(m_trackPtr.value()));
			m_trackPtr = none;
		}

		if (board.rect().rightPressed() || m_trackTime > 0)
		{
			if (m_trackTime < 0)
			{
				static const double TRACK_TIME = Config::get<double>(U"PlayerAccessObject.trackTime");
				static const double TRACK_SPEED = Config::get<double>(U"PlayerAccessObject.trackSpeed");
				m_trackTime = TRACK_TIME;
				m_trackPtr = std::make_shared<TrackAccessObject>(body().center, -m_movement * TRACK_SPEED);
			}

			m_movement *= FAST_SPEED;
		}
		else
		{
			m_movement *= SLOW_SPEED;
		}

		if (board.rect().leftClicked())
		{
			m_makingLightPos = board.cursorPos();
		}
	}

	void PlayerAccessObject::update(const Terrain& terrain)
	{
		walk(m_movement, terrain);

		m_movement = Vec2::Zero();

		// 距離の変更の比率
		static const double DISTANCE_RATE = Config::get<double>(U"AccessLight.Rate.distance");

		light()
			.setSourcePos(body().center)
			.setDistanceFromArea(m_lightArea, DISTANCE_RATE)
			.update(terrain);
	}

	void PlayerAccessObject::draw() const
	{
		TextureAsset(U"PlayerAccessObject").drawAt(body().center);
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

		// 光の生成
		if (m_makingLightPos)
		{
			makeLight(guidToObject, typeToGuidSet);
			m_makingLightPos = none;
		}
	}

	void PlayerAccessObject::makeLight(const GuidToObject& guidToObject, const TypeToGuidSet& typeToGuidSet)
	{
		const Vec2 cursorPos = m_makingLightPos.value();

		// 追跡対象のguid
		Optional<String> chasingGuid = none;
		for (const auto& guid : typeToGuidSet.find(Type::ENEMY)->second)
		{
			if (getObject(guid, guidToObject).body().contains(cursorPos))
			{
				chasingGuid = guid;
			}
		}
		for (const auto& guid : typeToGuidSet.find(Type::GOAL)->second)
		{
			if (getObject(guid, guidToObject).body().contains(cursorPos))
			{
				chasingGuid = guid;
			}
		}

		Ptr ptr = nullptr;
		if (chasingGuid)
		{
			ptr = std::make_shared<ChasingMinionAccessObject>(body().center, chasingGuid.value());
		}
		else if (light().contains(cursorPos))
		{
			ptr = std::make_shared<ProtectingMinionAccessObject>(body().center);
		}
		else
		{
			ptr = std::make_shared<SearchingMinionAccessObject>(body().center);
		}

		const double minionLightArea = ptr->light().area();
		if (ptr != nullptr && minionLightArea < m_lightArea)
		{
			m_lightArea -= minionLightArea;
			makeObject(std::move(ptr));
		}
	}
}
