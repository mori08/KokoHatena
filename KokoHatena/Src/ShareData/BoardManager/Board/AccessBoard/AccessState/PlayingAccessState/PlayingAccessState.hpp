#pragma once

#include "../AccessState.hpp"

namespace Kokoha
{
	/// <summary>
	/// ゲームを遊んでいるとき(AccessObjectの更新/描画を行っているとき)のAccessState
	/// </summary>
	class PlayingAccessState : public AccessState
	{
		Optional<std::shared_ptr<AccessState>> update(
			AccessObject::GuidToObject& objectMap,
			AccessObject::TypeToGuidSet& typeToGuidSet,
			BoardRequest&) override;

		bool isUpdatingObject() const override;

		void draw() const override;

	};
}
