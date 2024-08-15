#pragma once

#include "../../AccessObject.hpp"

namespace Kokoha
{
	class LastGoalAccessObject : public AccessObject
	{
	private:

		double m_angle;

		Vec2 m_playerPos;

	public:

		LastGoalAccessObject(const Vec2& pos);

	protected:

		virtual void update(const Terrain& terrain) override;

		virtual void draw() const override;

		virtual void checkOthers(const Terrain& terrain, const GuidToObject& guidToObject, const TypeToGuidSet& typeToGuidSet) override;

	};
}
