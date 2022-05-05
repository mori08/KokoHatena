#pragma once

#include "../Scene.hpp"
#include "../../ButtonSet/ButtonSet.hpp"

namespace Kokoha
{
	/// <summary>
	/// タイトルシーン
	/// </summary>
	class TitleScene : public MyApp::Scene
	{
	private:

		// ボタンの管理
		ButtonSet m_buttonSet;

		// カーソルの幅
		double m_cursorWidth;

		// カーソルの横に出る線の長さ
		double m_cursorLineLength;

		// カーソルの横に出る線の不透明度
		double m_cursorLineAlpha;

	public:

		TitleScene(const InitData& init);

		void update() override;

		void updateFadeOut(double) override;

		void draw() const override;

	};
}