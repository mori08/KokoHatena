#pragma once

#include "../AccessObject.hpp"

namespace Kokoha
{
	class PlayerAccessObject : public AccessObject
	{
	private:

		// inputで決定する移動量
		Vec2 m_movement;

		// true のとき自分の周りを照らす , false のとき遠くを照らす
		bool m_lightMode;

		// 光を出す方向
		double m_direction;

	public:

		PlayerAccessObject(const Vec2& pos);

	private:

		void input(const BoardArg& board) override;

		void update(const Terrain& terrain) override;

		void draw() const override;

		void checkOthers(const Terrain&, const GuidToObject& guidToObject, const TypeToGuidSet& typeToGuidSet) override;

	private:

		/// <summary>
		/// 光の情報の入力
		/// </summary>
		void inputLight();

	};
}
