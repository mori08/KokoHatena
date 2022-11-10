#pragma once

#include "../AccessObject.hpp"

namespace Kokoha
{
	class LightAccessObject : public AccessObject
	{
	public:

		LightAccessObject(const Vec2& pos);

	private:

		void drawLight() const override;

	};
}