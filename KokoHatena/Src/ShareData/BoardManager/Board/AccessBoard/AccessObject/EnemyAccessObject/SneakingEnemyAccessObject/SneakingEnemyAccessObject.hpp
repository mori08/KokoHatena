#pragma once
#include "../EnemyAccessObject.hpp"

namespace Kokoha
{
	class SneakingEnemyAccessObject : public EnemyAccessObject
	{
	private:

		// 待機時間
		double m_waitingSecond;

	public:

		SneakingEnemyAccessObject(const Vec2& pos);

	private:

		void update(const Terrain& terrain) override;

		void checkOthers(const Terrain& terrain, const GuidToObject& guidToObject, const TypeToGuidSet& typeToGuidSet) override;

	};
}
