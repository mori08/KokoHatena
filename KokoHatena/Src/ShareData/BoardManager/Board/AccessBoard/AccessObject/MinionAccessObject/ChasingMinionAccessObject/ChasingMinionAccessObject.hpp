#pragma once
#include "../MinionAccessObject.hpp"

namespace Kokoha
{
	class ChasingMinionAccessObject : public MinionAccessObject
	{
	private:

		// 追いかけるオブジェクトのguid
		const String m_chasingGuid;

	public:

		ChasingMinionAccessObject(const Vec2& pos, const String& chasingGuid);

	protected:

		void setGoal(
			const Terrain& terrain,
			const GuidToObject& guidToObject,
			const TypeToGuidSet& typeToGuidSet
		) override;

		double maxLightArea() const override;

	};
}
