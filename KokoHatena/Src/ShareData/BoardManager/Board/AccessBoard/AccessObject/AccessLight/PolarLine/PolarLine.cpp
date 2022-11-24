#include "PolarLine.hpp"
#include "../../../../../../../MyLibrary/MyLibrary.hpp"

namespace
{
	constexpr double EPSILON = 1e-10;
}

namespace Kokoha
{
	PolarLine::PolarLine(const PolarPos& point1, const PolarPos& point2)
		: p1(point1.a - EPSILON, point1.r)
		, p2(point2.a + EPSILON, point2.r)
		, A(- p1.r * Sin(p1.a) + p2.r * Sin(p2.a))
		, B(+ p1.r * Cos(p1.a) - p2.r * Cos(p2.a))
		, C(p1.r * p2.r * Sin(p2.a - p1.a))
	{
	}

	Optional<double> PolarLine::r(double a) const
	{
		// ���̍��� ACos(a)+BSin(a)
		const double L = A * Cos(a) + B * Sin(a);

		// C == 0  -> 2�_��ʂ钼���� r=a�ƕ��s�ȂƂ�
		// N/C < 0 -> r=a�ƌ�_�������Ȃ�(�t��r=a+Pi�ƌ�_������)
		if (C == 0 || C / L < 0) { return none; }
		return C / L;
	}

	std::list<double> PolarLine::a(double r) const
	{
		// ���ʎ�
		const double D = (A*A + B*B) * r*r - C*C;
		std::list<double> rtn;

		if (D < 0) { return rtn; }
		
		if (D == 0) 
		{ 
			const double angle = atan2(B*C, A*C); // ��_�̊p�x
			if (clockwise(p1.a, angle, p2.a)) { rtn.push_back(angle); }
			return rtn; 
		}

		const double vD = Sqrt(D);

		// ��_�̍��W
		const double
			a1 = atan2(B*C + A*vD, A*C - B*vD),
			a2 = atan2(B*C - A*vD, A*C + B*vD);

		if (clockwise(p1.a, a1, p2.a)) { rtn.push_back(a1); }
		if (clockwise(p1.a, a2, p2.a)) { rtn.push_back(a2); }

		return rtn;
	}

	bool PolarLine::on(double r) const
	{
		if (p1.r < r || p2.r < r) { return true; }

		const double D = (A*A + B*B) * r*r - C*C;
		if (D <= 0) { return false; }

		const double vD = Sqrt(D);
		if (clockwise(p1.a, atan2(B*C + A*vD, A*C - B*vD), p2.a)) { return true; }
		if (clockwise(p1.a, atan2(B*C - A*vD, A*C + B*vD), p2.a)) { return true; }

		return false;
	}
}