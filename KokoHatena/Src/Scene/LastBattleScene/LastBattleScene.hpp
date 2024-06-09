#pragma once

#include "../Scene.hpp"
#include "../../ShareData/BoardManager/Board/AccessBoard/AccessBoard.hpp"

namespace Kokoha
{
	class LastBattleScene : public MyApp::Scene
	{
	private:

		AccessBoard m_accessBoard;

	public:

		LastBattleScene(const InitData& init);

	private:

		void update() override;

		void draw() const override;

	};
}
