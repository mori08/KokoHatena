#pragma once

#include "../AccessState.hpp"

namespace Kokoha
{
	class SuccessAccessState : public AccessState
	{
	public:

		SuccessAccessState() {}

	private:

		void input(const Vec2&) override;

		Optional<std::shared_ptr<AccessState>> update(
			AccessObject::GuidToObject& objectMap,
			AccessObject::TypeToGuidSet& typeToGuidSet) override;

		bool isUpdatingObject() const override;

		void draw() const override;

	};
}