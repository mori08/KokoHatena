#pragma once

#include "../AccessState.hpp"

namespace Kokoha
{
	/// <summary>
	/// プレイヤーが敵と接触したときのAccessState
	/// </summary>
	class FailedAccessState : public AccessState
	{
	private:

		// 失敗演出を出すマスとプレイヤーの距離
		double m_failedDistance;

		// プレイヤーのマス座標
		const Point m_playerSquare;

	public:

		/// <returns> プレイヤーのマス座標 </returns>
		FailedAccessState(const Point& playerSquare);

	private:

		void input(const Vec2&) override;

		Optional<std::shared_ptr<AccessState>> update(
			AccessObject::GuidToObject& objectMap,
			AccessObject::TypeToGuidSet& typeToGuidSet) override;

		bool isUpdatingObject() const override;

		void draw() const override;

	};
}