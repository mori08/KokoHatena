#pragma once


#include "../Scene.hpp"


namespace Kokoha
{
	/// <summary>
	/// �^�C�g���V�[��
	/// </summary>
	class TitleScene : public MyApp::Scene
	{
	public:

		TitleScene(const InitData& init);

		void update() override;

		void draw() const override;

	};
}