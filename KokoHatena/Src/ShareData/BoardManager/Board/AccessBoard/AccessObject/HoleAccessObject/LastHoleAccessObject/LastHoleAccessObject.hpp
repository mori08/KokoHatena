#pragma once

#include "../HoleAccessObject.hpp"
#include "../../EnemyAccessObject/LastEnemyAccessObject/LastEnemyAccessObject.hpp"

namespace Kokoha
{
	class LastHoleAccessObject : public HoleAccessObject<LastEnemyAccessObject>
	{
	private:

		double m_angleFromGoal;

		Vec2 m_goalPos;

	public:

		LastHoleAccessObject(const Vec2& pos, double angleFromGoal);

	private:

		void update(const Terrain& terrain) override;

		void checkOthers(const Terrain& terrain, const GuidToObject& guidToObject, const TypeToGuidSet& typeToGuidSet) override;

		size_t enemySizeLimit() const override;

		double enemyMakeTime() const override;
	};
}
