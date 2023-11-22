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
	MinionAccessObject::MinionAccessObject(const Vec2& pos)
		: AccessObject(Type::MINION, pos)
		, m_trackTime(trackTime())
	{
		m_goal = pos;

		// 光の初期面積
		static const double LIGHT_AREA = Config::get<double>(U"MinionAccessObject.lightArea");
		// 光の明るさ
		static const double LIGHT_ALPHA = Config::get<double>(U"MinionAccessObject.lightAlpha");
		
		m_lightArea = LIGHT_AREA;
		light()
			.setAlpha(LIGHT_ALPHA)
			.setCentralAngle(Math::TwoPi)
			.setDistanceFromArea(LIGHT_AREA)
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

	void MinionAccessObject::setGoal(const Terrain&, const GuidToObject&, const TypeToGuidSet&)
	{
	}
}
