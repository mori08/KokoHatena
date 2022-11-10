#include "LightAccessObject.hpp"
#include "../../../../../../MyLibrary/MyLibrary.hpp"

namespace Kokoha
{
	LightAccessObject::LightAccessObject(const Vec2& pos)
		: AccessObject(Type::LIGHT, pos)
	{
	}

	void LightAccessObject::drawLight() const
	{
		Circle(body().center, 100).draw(MyWhite);
	}
}