#pragma once
#include "../TrackAccessObject.hpp"

namespace Kokoha
{
	class LastTrackAccessObject : public TrackAccessObject
	{
	private:

		// true のとき ゴールを追う , false のとき Playerを追う
		bool m_isChasingGoal;

	public:

		LastTrackAccessObject(const Vec2& pos, const Vec2& movement, int32 powerUpLevel);

	private:

		void update(const Terrain& terrain) override;

		void checkOthers(const Terrain&, const GuidToObject& guidToObject, const TypeToGuidSet& typeToGuidSet) override;
	};
}
