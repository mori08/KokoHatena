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
	protected:

		// 外殻描画用SliceTexture
		SliceTexture m_bodyTexture;

		// 顔描画用SliceTexture
		SliceTexture m_faceTexture;

		// 移動先の座標
		Vec2 m_targetPos;

		// 移動の速さ
		double m_speed;

	public:

		EnemyAccessObject(const Vec2& pos);

	protected:

		virtual void update(const Terrain&) override;

		virtual void draw() const override;

		virtual void checkOthers(const Terrain& terrain, const GuidToObject& guidToObject, const TypeToGuidSet& typeToGuidSet) override;

	};
}
