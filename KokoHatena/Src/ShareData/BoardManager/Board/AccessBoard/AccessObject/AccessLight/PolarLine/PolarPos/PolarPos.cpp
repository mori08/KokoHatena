#include "PolarPos.hpp"
#include "../../../../../../../../MyLibrary/MyLibrary.hpp"

namespace Kokoha
{
	PolarPos::PolarPos(double angle, double distance)
		: a(angle)
		, r(distance)
	{
	}

	PolarPos::PolarPos(const PolarPos& another)
		: a(another.a)
		, r(another.r)
	{
	}

	PolarPos::PolarPos(const Vec2& pos, const Vec2& originPos, double initalLineAngle)
		: a(twoVecToAngle(angleToVec(initalLineAngle), pos - originPos))
		, r(pos.distanceFrom(originPos))
	{
	}

	Vec2 PolarPos::toOrthoPos(const Vec2& originPos, double initialLineAngle) const
	{
		return originPos + r * angleToVec(a + initialLineAngle);
	}
}
