#pragma once

#include "../AccessObject.hpp"

namespace Kokoha
{
	class MinionAccessObject : public AccessObject
	{
	private:

		// –Ú“I’n
		Vec2 m_goal;

		// ˆÚ“®—Ê
		double m_direction;

	public:

		MinionAccessObject(const Vec2& pos);

	private:

		void update(const Terrain& terrain) override;

		void draw() const override;

	};
}