#pragma once

#include "../AccessObject.hpp"

namespace Kokoha
{
	class PlayerAccessObject : public AccessObject
	{
	private:

		// inputで決定する移動量
		Vec2 m_movement;

		// 光の面積
		double m_lightArea;

		// noneでないとき光を生成 , 座標はカーソル位置
		Optional<Vec2> m_makingLightPos;

	public:

		PlayerAccessObject(const Vec2& pos);

	private:

		void input(const BoardArg& board) override;

		void update(const Terrain& terrain) override;

		void draw() const override;

		void checkOthers(const Terrain&, const GuidToObject& guidToObject, const TypeToGuidSet& typeToGuidSet) override;

	};
}
