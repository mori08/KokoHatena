#include "MinionAccessObject.hpp"
#include "../../../../../../MyLibrary/MyLibrary.hpp"
#include "../../../../../../Config/Config.hpp"
#include "../TrackAccessObject/TrackAccessObject.hpp"

namespace
{
	const double& trackTime()
	{
		static const double rtn = Kokoha::Config::get<double>(U"MinionAccessObject.trackTime");
		return rtn;
	}
}

namespace Kokoha
{
	MinionAccessObject::MinionAccessObject(const Vec2& pos, double lightArea)
		: AccessObject(Type::MINION, pos)
		, m_lightArea(lightArea)
		, m_trackTime(trackTime())
	{
		m_goal = pos;

		// 光の明るさ
		static const double LIGHT_ALPHA = Config::get<double>(U"MinionAccessObject.lightAlpha");

		light()
			.setAlpha(LIGHT_ALPHA)
			.setCentralAngle(Math::TwoPi)
			.setDistanceFromArea(m_lightArea)
			.on();
	}

	void MinionAccessObject::update(const Terrain& terrain)
	{
		static const double SPEED = Config::get<double>(U"MinionAccessObject.speed");
		walkToGoal(SPEED, m_goal, terrain);

		m_trackTime -= Scene::DeltaTime();
		if (m_trackTime < 0)
		{
			m_trackTime = trackTime();
			Ptr trackObjPtr = std::make_shared<TrackAccessObject>(body().center, Vec2::Zero());
			m_lightArea -= trackObjPtr->light().area();
			makeObject(std::move(trackObjPtr));
		}

		if (m_lightArea < 0)
		{
			light().off();
			erase();
		}
		else
		{
			light()
				.setSourcePos(body().center)
				.setDistanceFromArea(m_lightArea)
				.update(terrain);
		}
	}

	void MinionAccessObject::draw() const
	{
		body().drawFrame(2, MyBlack);
	}

	void MinionAccessObject::checkOthers(const Terrain& terrain, const GuidToObject& guidToObject, const TypeToGuidSet& typeToGuidSet)
	{
		setGoal(terrain, guidToObject, typeToGuidSet);

		// 敵とぶつかったら消える
	}
}
