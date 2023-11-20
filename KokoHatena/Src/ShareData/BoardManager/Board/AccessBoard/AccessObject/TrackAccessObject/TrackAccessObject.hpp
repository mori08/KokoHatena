#pragma once

#include "../AccessObject.hpp"

namespace Kokoha
{
	/// <summary>
	/// 光の粒のオブジェクト
	/// MinionAccessObject が消えるときに生成
	/// Playerに衝突すると消滅
	/// </summary>
	class TrackAccessObject : public AccessObject
	{
	private:

		Vec2 m_playerPos;

		Vec2 m_movement;

	public:

		/// <param name="pos"> 初期座標 </param>
		/// <param name="movement"> 初期移動量 </param>
		TrackAccessObject(const Vec2& pos, const Vec2& movement);

	private:

		void update(const Terrain& terrain) override;

		void checkOthers(const Terrain&, const GuidToObject& guidToObject, const TypeToGuidSet& typeToGuidSet) override;
	};
}
