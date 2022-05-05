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

	private:

		/// <summary>
		/// ロゴの描画
		/// </summary>
		void drawLogo() const;

		/// <summary>
		/// ボタンの描画
		/// </summary>
		void drawButton() const;

		/// <summary>
		/// シェーダ時に使用するシフトのベクトル
		/// </summary>
		/// <param name="frequency"> 頻度         </param>
		/// <param name="shift"    > ずれの大きさ </param>
		/// <returns> シフトのベクトル </returns>
		static Float2 makeShift(double frequency, double shift);

	};
}