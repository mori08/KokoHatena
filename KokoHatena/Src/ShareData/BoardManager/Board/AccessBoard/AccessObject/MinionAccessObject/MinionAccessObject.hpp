#pragma once

#include "../AccessObject.hpp"

namespace Kokoha
{
	class MinionAccessObject : public AccessObject
	{
	private:

		// 目的地
		Vec2 m_goal;

		// 移動量
		double m_direction;

		// 光の面積
		double m_lightArea;

		// Trackを作成する時間
		double m_trackTime;

	public:

		MinionAccessObject(const Vec2& pos);

	private:

		void update(const Terrain& terrain) override;

		void draw() const override;

	};
}
