#pragma once

#include "../AccessState.hpp"

namespace Kokoha
{
	class SuccessAccessState : public AccessState
	{
	private:

		// プレイヤーの座標
		const Vec2 m_playerPos;

		// 光の輪の半径
		double m_lightRadius;

		// 光の不透明度
		double m_lightAlpha;

	public:

		SuccessAccessState(const Vec2& playerPos);

	private:

		void input(const Vec2&) override;

		Optional<std::shared_ptr<AccessState>> update(
			AccessObject::GuidToObject& objectMap,
			AccessObject::TypeToGuidSet& typeToGuidSet) override;

		bool isUpdatingObject() const override;

		void draw() const override;

	};
}