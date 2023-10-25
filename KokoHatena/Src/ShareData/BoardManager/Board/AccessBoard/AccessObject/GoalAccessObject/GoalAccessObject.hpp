#pragma once

#include "../AccessObject.hpp"

namespace Kokoha
{
	class GoalAccessObject : public AccessObject
	{
	public:

		GoalAccessObject(const Vec2& pos);

	private:

		void update(const Terrain& terrain) override;

		void draw() const override;

		void checkOthers(const Terrain& terrain, const GuidToObject& guidToObject, const TypeToGuidSet& typeToGuidSet) override;

	};
}
