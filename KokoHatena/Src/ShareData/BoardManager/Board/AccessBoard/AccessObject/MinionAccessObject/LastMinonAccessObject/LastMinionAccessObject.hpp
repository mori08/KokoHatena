#pragma once
#include "../MinionAccessObject.hpp"

namespace Kokoha
{
	class LastMinionAccessObject : public MinionAccessObject
	{
	private:

		// 速度
		Vec2 m_velocity;

		// 強化レベル
		const int32 m_powerUpLevel;

	public:

		LastMinionAccessObject(const Vec2& pos, int32 powerUpLevel);

	private:

		void setGoal(
			const Terrain& terrain,
			const GuidToObject& guidToObject,
			const TypeToGuidSet& typeToGuidSet
		) override;

		double maxLightAreaFromLevel(int32 powerUpLevel) const;

		double maxLightArea() const override;

		void walkMinion(const Terrain& terrain) override;

		void makeTrack(const Vec2& movement) override;
	};
}
