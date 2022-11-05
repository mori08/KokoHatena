#include "AccessObject.hpp"
#include "../../../../../MyLibrary/MyLibrary.hpp"

namespace Kokoha
{
	AccessObject::AccessObject(const Type& type, const Circle& body)
		: m_type(type)
		, m_guid(makeGuid())
		, m_body(body)
	{
	}

	void AccessObject::input(const Vec2&)
	{
	}

	void AccessObject::update(const Terrain&)
	{
	}

	void AccessObject::checkOthers(const Terrain&, const std::unordered_map<String, Ptr>&, const std::unordered_map<Type, std::list<String>>&)
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
		return false;
	}

}