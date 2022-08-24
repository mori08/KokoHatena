#pragma once

#include "../SelectRecordScene.hpp"

namespace Kokoha
{
	class SelectLoadRecordScene : public SelectRecordScene
	{
	public:

		SelectLoadRecordScene(const InitData& init);

		void update() override;

		void draw() const override;

	};
}