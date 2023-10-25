#pragma once

#include "../AccessObject.hpp"

namespace Kokoha
{
	class EnemyAccessObject : public AccessObject
	{
	private:

		// プレイヤーの座標
		Vec2 m_playerPos;

	public:

		EnemyAccessObject(const Vec2& pos);

	private:

		void update(const Terrain& terrain) override;

		void draw() const override;

		void checkOthers(const Terrain& terrain, const GuidToObject& guidToObject, const TypeToGuidSet& typeToGuidSet) override;

	};
}
