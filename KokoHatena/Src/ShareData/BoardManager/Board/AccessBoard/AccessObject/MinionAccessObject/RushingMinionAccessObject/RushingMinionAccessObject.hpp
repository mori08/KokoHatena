#pragma once
#include "../MinionAccessObject.hpp"

namespace Kokoha
{
	/// <summary>
	/// 直進する
	/// </summary>
	class RushingMinionAccessObject : public MinionAccessObject
	{
	private:

		// 進む方向
		const Vec2 m_direction;

		// 0未満になったとき削除
		double m_erasingTime;

	public:

		/// <param name="pos"> 座標 </param>
		/// <param name="direction"> 進む方向 </param>
		RushingMinionAccessObject(const Vec2& pos, const Vec2& direction);

	private:

		void setGoal(
			const Terrain& terrain,
			const GuidToObject& guidToObject,
			const TypeToGuidSet& typeToGuidSet
		) override;

		double maxLightArea() const override;

		void walkMinion(const Terrain& terrain) override;

	};
}
