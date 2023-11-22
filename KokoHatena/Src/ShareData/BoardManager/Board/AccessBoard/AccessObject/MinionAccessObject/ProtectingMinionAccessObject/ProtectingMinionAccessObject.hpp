#pragma once
#include "../MinionAccessObject.hpp"

namespace Kokoha
{
	/// <summary>
	/// プレイヤーの周りを動く<->敵の攻撃 を行うMinionAccessObject
	/// </summary>
	class ProtectingMinionAccessObject : public MinionAccessObject
	{
	private:

		double m_angle;

	public:

		ProtectingMinionAccessObject(const Vec2& pos);

	public:

		void setGoal(
			const Terrain& terrain,
			const GuidToObject& guidToObject,
			const TypeToGuidSet& typeToGuidSet
		) override;

	};
}
