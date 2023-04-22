#pragma once

#include "../AccessState.hpp"

namespace Kokoha
{
	class SuccessAccessState : public AccessState
	{
	private:

		// �v���C���[�̍��W
		const Vec2 m_playerPos;

		// ���̗ւ̔��a
		double m_lightRadius;

		// ���̕s�����x
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