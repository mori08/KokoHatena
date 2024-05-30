#pragma once

#include "../GoalAccessObject.hpp"

namespace Kokoha
{
	class MovingGoalAccessObject : public GoalAccessObject
	{
	private:

		Vec2 m_targetPos;

		double m_waitingSecond;

	public:

		MovingGoalAccessObject(const Vec2& pos);

	private:

		void update(const Terrain& terrain) override;
	};
}
