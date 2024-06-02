#pragma once

#include "../EnemyAccessObject.hpp"

namespace Kokoha
{
	class DefencingEnemyAccessObject : public EnemyAccessObject
	{
	private:

		// true のとき追跡中 , false のときゴールの周りを巡回中
		bool m_isChasing;

		// 視界
		AccessLight m_visualField;

	public:

		DefencingEnemyAccessObject(const Vec2& pos);

	private:

		void update(const Terrain& terrain) override;

		void draw() const override;

		void checkOthers(const Terrain& terrain, const GuidToObject& guidToObject, const TypeToGuidSet& typeToGuidSet) override;

	};
}
