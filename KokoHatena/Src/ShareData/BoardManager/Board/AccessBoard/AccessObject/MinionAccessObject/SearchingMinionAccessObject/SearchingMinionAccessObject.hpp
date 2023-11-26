#pragma once
#include "../MinionAccessObject.hpp"

namespace Kokoha
{
	/// <summary>
	/// ランダム移動->ゴール追跡を行うMinionAccessObject
	/// </summary>
	class SearchingMinionAccessObject : public MinionAccessObject
	{
	public:

		SearchingMinionAccessObject(const Vec2& pos);

	protected:

		void setGoal(
			const Terrain& terrain,
			const GuidToObject& guidToObject,
			const TypeToGuidSet& typeToGuidSet
		) override;

		double maxLightArea() const override;

	};
}
