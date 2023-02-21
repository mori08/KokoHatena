#pragma once

#include "../AccessState.hpp"

namespace Kokoha
{
	/// <summary>
	/// �Q�[����V��ł���Ƃ�(AccessObject�̍X�V/�`����s���Ă���Ƃ�)��AccessState
	/// </summary>
	class PlayingAccessState : public AccessState
	{
	private:

		// true �̂Ƃ�Player���쐬����
		bool m_isMakingMinion;

	private:

		void input(const Vec2& cursorPos) override;

		Optional<std::shared_ptr<AccessState>> update(
			AccessObject::GuidToObject& objectMap,
			AccessObject::TypeToGuidSet& typeToGuidSet) override;

		bool isUpdatingObject() const override;

		void draw() const override;

	};
}