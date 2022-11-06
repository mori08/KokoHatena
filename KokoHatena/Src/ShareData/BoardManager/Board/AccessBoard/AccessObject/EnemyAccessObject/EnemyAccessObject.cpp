#include "EnemyAccessObject.hpp"
#include "../../../../../../Config/Config.hpp"
#include "../../../../../../MyLibrary/MyLibrary.hpp"

namespace Kokoha
{
	EnemyAccessObject::EnemyAccessObject(const Vec2& pos)
		: AccessObject(Type::ENEMY, pos)
	{
	}

	void EnemyAccessObject::update(const Terrain& terrain)
	{
		static double SPEED = Config::get<double>(U"EnemyAccessObject.speed");
		walkToGoal(SPEED, m_playerPos, terrain);
	}

	void EnemyAccessObject::draw() const
	{
		m_body.drawFrame(2, Palette::Black);
	}

	void EnemyAccessObject::checkOthers(const Terrain&, const GuidToObject& guidToObject, const TypeToGuidSet& typeToGuidSet)
	{
		for (const String& guid : typeToGuidSet.find(Type::PLAYER)->second)
		{
			m_playerPos = guidToObject.find(guid)->second->body().center;
		}
	}
}