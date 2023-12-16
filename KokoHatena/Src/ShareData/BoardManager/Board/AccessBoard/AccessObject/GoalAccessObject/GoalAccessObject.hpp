#pragma once

#include "../AccessObject.hpp"
#include "../../../../../../MyLibrary/SliceTexture/SliceTexture.hpp"

namespace Kokoha
{
	class GoalAccessObject : public AccessObject
	{
	private:

		// ゴールの画像
		SliceTexture m_texture;

	public:

		GoalAccessObject(const Vec2& pos);

	private:

		void update(const Terrain& terrain) override;

		void draw() const override;

		void checkOthers(const Terrain& terrain, const GuidToObject& guidToObject, const TypeToGuidSet& typeToGuidSet) override;

	};
}
