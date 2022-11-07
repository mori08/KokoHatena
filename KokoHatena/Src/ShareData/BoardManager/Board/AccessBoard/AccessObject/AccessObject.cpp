#include "AccessObject.hpp"
#include "../../../../../MyLibrary/MyLibrary.hpp"
#include "../../../../../Config/Config.hpp"

namespace Kokoha
{
	AccessObject::AccessObject(const Type& type, const Circle& body)
		: m_type(type)
		, m_guid(makeGuid())
		, m_isErase(false)
		, m_body(body)
	{
	}

	AccessObject::AccessObject(const Type& type, const Vec2& pos)
		: AccessObject(type, Circle(pos, Config::get<double>(U"AccessObject.radius")))
	{
	}

	void AccessObject::input(const Vec2&)
	{
	}

	void AccessObject::update(const Terrain&)
	{
	}

	void AccessObject::checkOthers(const Terrain&, const GuidToObject&, const TypeToGuidSet&)
	{
	}

	void AccessObject::draw() const
	{
	}

	void AccessObject::drawLight() const
	{
	}

	bool AccessObject::isEraseAble() const
	{
		return m_isErase;
	}

	Vec2 AccessObject::walk(Vec2 movement, const Terrain& terrain)
	{
		movement *= Scene::DeltaTime();
		Vec2 rtn = Vec2::Zero();

		if (terrain.isWalkAble(m_body.center.movedBy(movement.x, 0)))
		{
			m_body.x += movement.x;
			rtn.x = movement.x;
		}

		if (terrain.isWalkAble(m_body.center.movedBy(0, movement.y)))
		{
			m_body.y += movement.y;
			rtn.y = movement.y;
		}

		return rtn;
	}

	Vec2 AccessObject::walkToGoal(double speed, const Vec2& goal, const Terrain& terrain)
	{
		return goal.distanceFrom(m_body.center) < speed * Scene::DeltaTime()
			? Vec2::Zero()
			: walk(speed * terrain.getPath(m_body.center, goal), terrain);
	}

}