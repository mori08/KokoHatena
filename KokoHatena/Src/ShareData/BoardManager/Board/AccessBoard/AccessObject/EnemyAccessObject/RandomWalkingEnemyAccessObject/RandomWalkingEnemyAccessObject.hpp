#pragma once

#include "../EnemyAccessObject.hpp"

namespace Kokoha
{
	/// <summary>
	/// ランダムに移動する敵オブジェクト
	/// </summary>
	class RandomWalkingEnemyAccessObject : public EnemyAccessObject
	{
	private:

		// 目的地での待機時間
		double m_waitingSecond;

	public:

		RandomWalkingEnemyAccessObject(const Vec2& pos);

	private:

		void update(const Terrain& terrain) override;

	};
}
