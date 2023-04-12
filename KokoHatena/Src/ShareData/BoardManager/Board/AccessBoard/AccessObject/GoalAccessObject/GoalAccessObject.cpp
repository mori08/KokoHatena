#include "GoalAccessObject.hpp"

namespace Kokoha
{
	GoalAccessObject::GoalAccessObject(const Vec2& pos)
		: AccessObject(Type::GOAL, pos)
	{
	}

	void GoalAccessObject::update(const Terrain& terrain)
	{
	}

	void GoalAccessObject::draw() const
	{
	}

	void GoalAccessObject::checkOthers(const Terrain& terrain, const GuidToObject& guidToObject, const TypeToGuidSet& typeToGuidSet)
	{
	}
}