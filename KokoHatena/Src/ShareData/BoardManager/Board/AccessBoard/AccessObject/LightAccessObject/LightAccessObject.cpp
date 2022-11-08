#include "LightAccessObject.hpp"

namespace Kokoha
{
	LightAccessObject::LightAccessObject(const Vec2& pos)
		: AccessObject(Type::LIGHT, pos)
	{
	}

	void LightAccessObject::draw() const
	{
		body().draw();
	}
}