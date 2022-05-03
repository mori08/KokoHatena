#pragma once


#include "../Scene.hpp"


namespace Kokoha
{
	/// <summary>
	/// タイトルシーン
	/// </summary>
	class TitleScene : public MyApp::Scene
	{
	public:

		TitleScene(const InitData& init);

		void update() override;

		void draw() const override;

	};
}