#pragma once

#include "../AccessObject.hpp"

namespace Kokoha
{
	class PlayerAccessObject : public AccessObject
	{
	private:

		// inputで決定する移動量
		Vec2 m_movement;

	public:

		PlayerAccessObject(const Vec2& pos);

	private:

		void input(const Vec2& cursorPos) override;

		void update(const Terrain& terrain) override;

		void draw() const override;

		void checkOthers(const Terrain&, const GuidToObject& guidToObject, const TypeToGuidSet& typeToGuidSet) override;

	};
}