#include "AccessLight.hpp"
#include "../../../../../../MyLibrary/MyLibrary.hpp"

namespace Kokoha
{
	AccessLight::AccessLight()
		: m_on(false)
		, m_sourcePos(Vec2::Zero())
		, m_directionAngle(0)
		, m_centralAngle(0)
		, m_distance(0)
		, m_alpha(0)
	{

	}

	void AccessLight::update(const Terrain& terrain)
	{
		m_on = true;
	}

	void AccessLight::draw() const
	{
		if (!m_on) { return; }

		Circle(m_sourcePos, m_distance)
			.draw(ColorF(MyWhite, m_alpha));
	}
}