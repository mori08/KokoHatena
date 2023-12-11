#pragma once
#include "../MinionAccessObject.hpp"

namespace Kokoha
{
	/// <summary>
	/// プレイヤーの周りを動く
	/// </summary>
	class ProtectingMinionAccessObject : public MinionAccessObject
	{
	public:

		ProtectingMinionAccessObject(const Vec2& pos);

	private:

		void setGoal(
			const Terrain& terrain,
			const GuidToObject& guidToObject,
			const TypeToGuidSet& typeToGuidSet
		) override;

		double maxLightArea() const override;

	};
}
