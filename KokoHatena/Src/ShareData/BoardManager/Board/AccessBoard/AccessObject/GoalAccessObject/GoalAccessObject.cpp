#include "GoalAccessObject.hpp"
#include "../../../../../../MyLibrary/MyLibrary.hpp"
#include "../../../../../../Config/Config.hpp"

namespace Kokoha
{
	GoalAccessObject::GoalAccessObject(const Vec2& pos)
		: AccessObject(Type::GOAL, pos)
		, m_texture(Config::get<SliceTexture>(U"GoalAccessObject.slice"))
	{
		m_texture.start(U"anim");
	}

	void GoalAccessObject::update(const Terrain&)
	{
		m_texture.update();
	}

	void GoalAccessObject::draw() const
	{
		m_texture.getTexture().drawAt(body().center);
	}

	void GoalAccessObject::checkOthers(const Terrain&, const GuidToObject&, const TypeToGuidSet&)
	{
	}
}
