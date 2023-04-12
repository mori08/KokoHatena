#pragma once

#include "../AccessState.hpp"

namespace Kokoha
{
	/// <summary>
	/// ƒQ[ƒ€‚ğ—V‚ñ‚Å‚¢‚é‚Æ‚«(AccessObject‚ÌXV/•`‰æ‚ğs‚Á‚Ä‚¢‚é‚Æ‚«)‚ÌAccessState
	/// </summary>
	class PlayingAccessState : public AccessState
	{
	private:

		// true ‚Ì‚Æ‚«Player‚ğì¬‚·‚é
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