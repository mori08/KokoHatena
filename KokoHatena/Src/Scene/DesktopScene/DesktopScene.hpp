#pragma once

#include "../Scene.hpp"
#include "../../ShareData/BoardManager/Board/Board.hpp"

namespace Kokoha
{
	/// <summary>
	/// Boardのリストを管理するシーン
	/// ゲームのメインの進行
	/// </summary>
	class DesktopScene : public MyApp::Scene
	{
	public:

		DesktopScene(const InitData& init);

	private:

		void update() override;

		void draw() const override;

	};
}