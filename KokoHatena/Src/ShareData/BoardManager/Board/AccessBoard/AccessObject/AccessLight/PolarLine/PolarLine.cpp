#include "PolarLine.hpp"

namespace
{
	constexpr double EPSILON = 1e-10;
}

namespace Kokoha
{
	PolarLine::PolarLine(const PolarPos& point1, const PolarPos& point2)
		: p1(point1.a - EPSILON, point1.r)
		, p2(point2.a + EPSILON, point2.r)
	{
	}

	Optional<double> PolarLine::r(double a) const
	{
		const double x = p1.r * Cos(p1.a) - p2.r * Cos(p2.a);
		const double y = p1.r * Sin(p1.a) - p2.r * Sin(p2.a);
		const double z = p1.r * p2.r * Sin(p2.a - p1.a);
		const double w = x * Sin(a) - y * Cos(a);

		// Abs(w) == 0 -> 2点を通る直線が r=aと並行なとき
		// z/w < 0     -> r=aと交点を持たない(逆にr=a+Piと交点を持つ)
		if (Abs(w) == 0 || z / w < 0) { return none; }
		return z / w;
	}
}