#include "MinionAccessObject.hpp"
#include "../../../../../../MyLibrary/MyLibrary.hpp"

namespace Kokoha
{
	MinionAccessObject::MinionAccessObject(const Vec2& pos)
		: AccessObject(Type::MINION, pos)
	{
		m_goal.x = Random(0.0, 600.0);
		m_goal.y = Random(0.0, 450.0);
		light()
			.setAlpha(0.3)
			.setCentralAngle(Math::TwoPi)
			.setDistance(50)
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

		uint64 time = Time::GetMicrosec();
		light()
			.setSourcePos(body().center)
			.setDirectionAngle(m_direction)
			.update(terrain);
		time = Time::GetMicrosec() - time;

		if (Scene::FrameCount() % 60 == 0)
		{
			Print << time * 1e-6;
		}
	}

	void MinionAccessObject::draw() const
	{
		body().drawFrame(2, MyBlack);
	}
}