#pragma once

#include "../EnemyAccessObject.hpp"

namespace Kokoha
{
	class ChasingEnemyAccessObject : public EnemyAccessObject
	{
	private:

		// 初期座標
		const Vec2& m_initalPos;

		// 向いてい角度
		double m_directionAngle;

		// 視界に入ったプレイヤーの座標
		Vec2 m_playerPos;

		// true のとき追跡中 , false のとき巡回中
		bool m_isChasing;

		// 視界
		AccessLight m_visualField;

	public:

		ChasingEnemyAccessObject(const Vec2& pos);

	private:

		void update(const Terrain& terrain) override;

		void checkOthers(const Terrain& terrain, const GuidToObject& guidToObject, const TypeToGuidSet& typeToGuidSet) override;

	};
}
