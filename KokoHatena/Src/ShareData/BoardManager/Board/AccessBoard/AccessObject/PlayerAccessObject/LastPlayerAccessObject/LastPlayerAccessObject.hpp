#pragma once
#include "../PlayerAccessObject.hpp"

namespace Kokoha
{
	class LastPlayerAccessObject : public PlayerAccessObject
	{
	private:

		// 強化レベル
		const int32 m_powerUpLevel;

	public:

		LastPlayerAccessObject(const Vec2& pos, int32 powerUpLevel);

	private:

		void makeLight(const GuidToObject& guidToObject, const TypeToGuidSet& typeToGuidSet) override;
	};
}
