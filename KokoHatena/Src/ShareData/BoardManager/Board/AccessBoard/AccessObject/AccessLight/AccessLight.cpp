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

	AccessLight& AccessLight::setDirectionAngle(double directionAngle, double rate)
	{
		internalDividingPoint(m_directionAngle, directionAngle, rate);
		return *this;
	}

	AccessLight& AccessLight::setCentralAngle(double centralAngle, double rate)
	{
		internalDividingPoint(m_centralAngle, centralAngle, rate);
		return *this;
	}

	AccessLight& AccessLight::setDistance(double distance, double rate)
	{
		internalDividingPoint(m_distance, distance, rate);
		return *this;
	}

	AccessLight& AccessLight::setAlpha(double alpha, double rate)
	{
		internalDividingPoint(m_alpha, alpha, rate);
		return *this;
	}

	void AccessLight::update(const Terrain& terrain)
	{
		if (!m_on || m_centralAngle == 0 || m_distance == 0 || m_alpha == 0)
		{
			return;
		}

		m_edgeList.clear();
		for (const std::pair<Point, Point>& edge : terrain.getEdge())
		{
			if (twoVecToAngle(edge.first - m_sourcePos, edge.second - edge.first) > 0)
			{
				m_edgeList.emplace_back(edge.first, edge.second);
			}
		}
	}

	void AccessLight::draw() const
	{
		if (!m_on) { return; }

		double direction = m_directionAngle - m_centralAngle / 2 + Math::HalfPi;

		while (direction < 0)
		{
			direction += Math::TwoPi;
		}
		while (direction > Math::TwoPi)
		{
			direction -= Math::TwoPi;
		}

		Circle(m_sourcePos, m_distance)
			.drawPie(
				direction, 
				m_centralAngle, ColorF(MyWhite, m_alpha)
			);

		for (const Line& line : m_edgeList)
		{
			line.drawArrow(4, Vec2(6, 6), Palette::Lime);
		}
	}
}