#pragma once

#include "../EnemyAccessObject.hpp"

namespace Kokoha
{
	class LastEnemyAccessObject : public EnemyAccessObject
	{
	private:

		// プレイヤーからの角度
		double m_angleFromPlayer;

		// 速度
		Vec2 m_velocity;

	public:

		LastEnemyAccessObject(const Vec2& pos);

	private:

		void update(const Terrain& terrain) override;

		void checkOthers(const Terrain& terrain, const GuidToObject& guidToObject, const TypeToGuidSet& typeToGuidSet) override;
		
	};
}
