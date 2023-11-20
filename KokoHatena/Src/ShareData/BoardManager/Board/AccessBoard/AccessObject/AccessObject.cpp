#include "AccessObject.hpp"
#include "../../../../../MyLibrary/MyLibrary.hpp"
#include "../../../../../Config/Config.hpp"

namespace Kokoha
{
	Optional<String> AccessObject::getFrontGuid(Type type, const TypeToGuidSet& typeToGuidSet)
	{
		const auto& guidSet = typeToGuidSet.find(type)->second;

		if (guidSet.empty()) { return none; }

		return *guidSet.begin();
	}

	const AccessObject& AccessObject::getObject(const String& guid, const GuidToObject& guidToObject)
	{
		if (guidToObject.count(guid))
		{
			return *(guidToObject.find(guid)->second);
		}

		throw Error(U"Faild to find object [guid : " + guid + U"]");
	}

	const AccessObject& AccessObject::getFrontObject(Type type, const GuidToObject& guidToObject, const TypeToGuidSet& typeToGuidSet)
	{
		if (auto guid = getFrontGuid(type, typeToGuidSet))
		{
			return getObject(*guid, guidToObject);
		}

		throw Error(U"Faild to find object [type : " + static_cast<int32>(type) + String(U"]"));
	}

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

	void AccessObject::setMakingObject(Ptr ptr, GuidToObject& objectMap, TypeToGuidSet& typeToGuidSet)
	{
		typeToGuidSet[ptr->type()].insert(ptr->guid());
		objectMap.try_emplace(ptr->guid(), ptr);
	}

	void AccessObject::input(const BoardArg&)
	{
	}

	void AccessObject::update(const Terrain&)
	{
	}

	void AccessObject::checkOthers(const Terrain&, const GuidToObject&, const TypeToGuidSet&)
	{
	}

	void AccessObject::addObjectList(std::list<AccessObject::Ptr>& makeObjectList)
	{
		while (!m_makeObjectList.empty())
		{
			makeObjectList.emplace_back(m_makeObjectList.front());
			m_makeObjectList.pop_front();
		}
	}

	bool AccessObject::isEraseAble() const
	{
		return m_isErase;
	}

	void AccessObject::draw() const
	{
	}

	void AccessObject::drawLight() const
	{
		m_light.draw();
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
