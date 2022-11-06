#pragma once

#include "../AccessObject.hpp"

namespace Kokoha
{
	class PlayerAccessObject : public AccessObject
	{
	private:

		Vec2 m_movement;

	public:

		PlayerAccessObject(const Vec2& pos);

	private:

		void input(const Vec2& cursorPos) override;

		void update(const Terrain& terrain) override;

		void draw() const override;

	};
}