#include "TitleScene.hpp"
#include "../../MyLibrary/MyLibrary.hpp"
#include "../../Config/Config.hpp"

namespace
{
	// ボタンサイズ
	const Size& buttonSize()
	{
		static const Size& size 
			= Kokoha::Config::get<Size>(U"TitleScene.buttonSize");
		return size;
	}

	// NEWGAMEボタン
	const Kokoha::Button& newGameButton()
	{
		static const Kokoha::Button button
			= Kokoha::Config::get<Kokoha::Button>(U"TitleScene.NewGameButton");
		return button;
	}

	// LoadGameボタン
	const Kokoha::Button& loadGameButton()
	{
		static const Kokoha::Button button
			= Kokoha::Config::get<Kokoha::Button>(U"TitleScene.LoadGameButton");
		return button;
	}

	// ExitGameボタン
	const Kokoha::Button& exitGameButton()
	{
		static const Kokoha::Button button
			= Kokoha::Config::get<Kokoha::Button>(U"TitleScene.ExitGameButton");
		return button;
	}
}

namespace Kokoha
{
	TitleScene::TitleScene(const InitData& init)
		: IScene(init)
		, m_cursorWidth(buttonSize().x)
		, m_cursorLineLength(Scene::Size().x)
		, m_cursorLineAlpha(0)
	{
		// ボタンの名前
		m_buttonSet.registerButton(newGameButton());
		m_buttonSet.registerButton(loadGameButton());
		m_buttonSet.registerButton(exitGameButton());
		m_buttonSet.setSelectedButton(loadGameButton().getName());

		m_buttonSet.setOnClickFunc(newGameButton().getName(), []() { Print << U"NewGameボタンが押された"; });
		m_buttonSet.setOnClickFunc(loadGameButton().getName(), []() { Print << U"LoadGameボタンが押された"; });
		m_buttonSet.setOnClickFunc(exitGameButton().getName(), []() { Print << U"ExitGameボタンが押された"; });
	}

	void TitleScene::update()
	{
		updateFadeOut(0);

		if (m_buttonSet.update())
		{
			m_cursorWidth      = 0.0;
			m_cursorLineLength = 0.0;
			m_cursorLineAlpha  = 1.0;
		}
	}

	void TitleScene::updateFadeOut(double)
	{
		// カーソルの移動の比率
		static const double CURSOR_MOVE_RATE = Config::get<double>(U"TitleScene.cursorMoveRate");

		// カーソルの幅の変更
		internalDividingPoint
		(
			m_cursorWidth,
			buttonSize().x,
			CURSOR_MOVE_RATE
		);

		// カーソルの横に出る線の長さの変更
		internalDividingPoint
		(
			m_cursorLineLength,
			Scene::Width(),
			CURSOR_MOVE_RATE
		);

		// カーソルの横に出る線の不透明度の変更
		internalDividingPoint
		(
			m_cursorLineAlpha,
			0,
			CURSOR_MOVE_RATE
		);
	}

	void TitleScene::draw() const
	{
		static const Point LOGO_POS = Config::get<Point>(U"TitleScene.logoPos");

		Scene::Rect().draw(MyBlack);

		// ロゴの描画
		TextureAsset(U"Logo").drawAt(LOGO_POS);

		// カーソルの描画
		getRectFromCenter
		(
			m_buttonSet.getSelectedButton().getRegion().center().asPoint(),
			Size((int32)m_cursorWidth, buttonSize().y)
		).draw(MyWhite);
		getRectFromCenter
		(
			m_buttonSet.getSelectedButton().getRegion().center().asPoint(),
			Size((int32)m_cursorLineLength, 1)
		).draw(ColorF(MyWhite, m_cursorLineAlpha));

		// ボタンの描画
		for (const auto& button : m_buttonSet.getButtonList())
		{
			Color color = (button.first == m_buttonSet.getSelectedButton().getName())
				? MyBlack
				: MyWhite;

			FontAsset(U"20")(button.first)
				.drawAt(button.second.getRegion().center(), color);
		}
	}
}