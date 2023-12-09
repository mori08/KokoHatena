#pragma once

#include "../AccessObject.hpp"
#include "../../../../../../MyLibrary/SliceTexture/SliceTexture.hpp"

namespace Kokoha
{
	class EnemyAccessObject : public AccessObject
	{
	private:

		// プレイヤーの座標
		Vec2 m_playerPos;

		// 外殻描画用SliceTexture
		SliceTexture m_bodyTexture;

		// 顔描画用SliceTexture
		SliceTexture m_faceTexture;

	public:

		EnemyAccessObject(const Vec2& pos);

	private:

		void update(const Terrain& terrain) override;

		void draw() const override;

		void checkOthers(const Terrain& terrain, const GuidToObject& guidToObject, const TypeToGuidSet& typeToGuidSet) override;

	};
}
