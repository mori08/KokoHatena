#include "EnemyAccessObject.hpp"
#include "../../../../../../Config/Config.hpp"

namespace Kokoha
{
	EnemyAccessObject::EnemyAccessObject(const Vec2& pos)
		: AccessObject(Type::ENEMY, pos)
		, m_bodyTexture(Config::get<SliceTexture>(U"EnemyAccessObject.body"))
		, m_faceTexture(Config::get<SliceTexture>(U"EnemyAccessObject.face"))
		, m_targetPos(pos)
	{
		m_bodyTexture.start(U"anim");
		m_faceTexture.start(U"normal");
	}

	void EnemyAccessObject::update(const Terrain& terrain)
	{
		m_bodyTexture.update();
		m_faceTexture.update();

		walkToGoal(m_speed, m_targetPos, terrain);
	}

	void EnemyAccessObject::draw() const
	{
		m_bodyTexture.getTexture().drawAt(body().center);
		m_faceTexture.getTexture().drawAt(body().center);
	}

	void EnemyAccessObject::checkOthers(const Terrain&, const GuidToObject& guidToObject, const TypeToGuidSet& typeToGuidSet)
	{
		for (const String& guid : typeToGuidSet.find(Type::MINION)->second)
		{
			if (getObject(guid, guidToObject).body().intersects(body()))
			{
				erase();
			}
		}
	}
}
