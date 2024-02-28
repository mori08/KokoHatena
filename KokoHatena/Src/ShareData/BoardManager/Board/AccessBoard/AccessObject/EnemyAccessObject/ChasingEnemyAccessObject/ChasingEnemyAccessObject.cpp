#include "ChasingEnemyAccessObject.hpp"
#include "../../../../../../../MyLibrary/MyLibrary.hpp"

namespace Kokoha
{
	ChasingEnemyAccessObject::ChasingEnemyAccessObject(const Vec2& pos)
		: EnemyAccessObject(pos)
		, m_initalPos(pos)
		, m_playerPos(pos)
		, m_isChasing(false)
		, m_directionAngle(m_directionAngle)
	{
		// TODO: 定数を準備
		m_visualField
			.setColor(MyBlack)
			.setAlpha(0.3)
			.setCentralAngle(1.0)
			.setDistance(80)
			.setDirectionAngle(m_directionAngle)
			.setSourcePos(pos)
			.on()
		;
	}

	void ChasingEnemyAccessObject::update(const Terrain& terrain)
	{

	}

	void ChasingEnemyAccessObject::checkOthers(const Terrain& terrain, const GuidToObject& guidToObject, const TypeToGuidSet& typeToGuidSet)
	{

		checkOthers(terrain, guidToObject, typeToGuidSet);
	}
}
