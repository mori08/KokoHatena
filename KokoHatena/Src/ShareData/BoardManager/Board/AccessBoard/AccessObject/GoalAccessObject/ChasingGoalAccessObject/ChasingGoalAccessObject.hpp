#pragma once

#include "../GoalAccessObject.hpp"

namespace Kokoha
{
	class ChasingGoalAccessObject : public GoalAccessObject
	{
	private:

		Vec2 m_targetPos;

	public:

		ChasingGoalAccessObject(const Vec2& pos);

	private:

		void update(const Terrain& terrain) override;

		void checkOthers(const Terrain& terrain, const GuidToObject& guidToObject, const TypeToGuidSet& typeToGuidSet) override;
	};
}
