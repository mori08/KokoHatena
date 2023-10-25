#include "GoalAccessObject.hpp"
#include "../../../../../../MyLibrary/MyLibrary.hpp"

namespace Kokoha
{
	GoalAccessObject::GoalAccessObject(const Vec2& pos)
		: AccessObject(Type::GOAL, pos)
	{
	}

	void GoalAccessObject::update(const Terrain&)
	{
	}

	void GoalAccessObject::draw() const
	{
		body().drawFrame(2, MyBlack);
	}

	void GoalAccessObject::checkOthers(const Terrain&, const GuidToObject&, const TypeToGuidSet&)
	{
	}
}
