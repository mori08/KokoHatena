#pragma once

#include "../AccessObject.hpp"
#include "../../../../../../MyLibrary/SliceTexture/SliceTexture.hpp"

namespace Kokoha
{
	/// <summary>
	/// 静止した敵オブジェクト
	/// （他の敵オブジェクトの基底クラスとしても使う）
	/// </summary>
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

		virtual void update(const Terrain&) override;

		virtual void draw() const override;

		void checkOthers(const Terrain& terrain, const GuidToObject& guidToObject, const TypeToGuidSet& typeToGuidSet) override;

	};
}
