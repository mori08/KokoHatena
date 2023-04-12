#pragma once

#include "../AccessState.hpp"

namespace Kokoha
{
	/// <summary>
	/// �v���C���[���G�ƐڐG�����Ƃ���AccessState
	/// </summary>
	class FailedAccessState : public AccessState
	{
	private:

		// ���s���o���o���}�X�ƃv���C���[�̋���
		double m_failedDistance;

		// �v���C���[�̃}�X���W
		const Point m_playerSquare;

	public:

		/// <returns> �v���C���[�̃}�X���W </returns>
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