#include "MinionAccessObject.hpp"
#include "../../../../../../MyLibrary/MyLibrary.hpp"

namespace Kokoha
{
	MinionAccessObject::MinionAccessObject(const Vec2& pos)
		: AccessObject(Type::MINION, pos)
	{
		m_goal.x = Random(0.0, 600.0);
		m_goal.y = Random(0.0, 450.0);
		m_direction = 0;
		light()
			.setAlpha(0.3)
			.setCentralAngle(Math::TwoPi)
			.setDistance(40)
			.on();
	}

	void MinionAccessObject::update(const Terrain& terrain)
	{
		const Vec2 movement = walkToGoal(60, m_goal, terrain);
		if (movement.isZero())
		{
			m_goal.x = Random(0.0, 600.0);
			m_goal.y = Random(0.0, 450.0);
		}
		else
		{
			const double d = twoVecToAngle(angleToVec(m_direction), movement);
			internalDividingPoint(m_direction, m_direction + d, 0.2);
		}

		light()
			.setSourcePos(body().center)
			.setDirectionAngle(m_direction)
			.update(terrain);
	}

	void MinionAccessObject::draw() const
	{
		body().drawFrame(2, MyBlack);
	}
}
