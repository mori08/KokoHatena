#include "TitleScene.hpp"
#include "../../MyLibrary/MyLibrary.hpp"
#include "../../MyPixelShader/MyPixelShader.hpp"
#include "../../Config/Config.hpp"

namespace
{
	/*
	* �萔�o�b�t�@ (PS_1)
	* RGB�̂���
	*/
	struct Shift
	{
		Float2 g_rShift;
		Float2 g_gShift;
		Float2 g_bShift;
		Float2 unusedB = {};
	};

	// �{�^���T�C�Y
	const Size& buttonSize()
	{
		static const Size& size 
			= Kokoha::Config::get<Size>(U"TitleScene.buttonSize");
		return size;
	}

	// NEWGAME�{�^��
	const Kokoha::Button& newGameButton()
	{
		static const Kokoha::Button button
			= Kokoha::Config::get<Kokoha::Button>(U"TitleScene.NewGameButton");
		return button;
	}

	// LoadGame�{�^��
	const Kokoha::Button& loadGameButton()
	{
		static const Kokoha::Button button
			= Kokoha::Config::get<Kokoha::Button>(U"TitleScene.LoadGameButton");
		return button;
	}

	// ExitGame�{�^��
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
		// �{�^���̖��O
		m_buttonSet.registerButton(newGameButton());
		m_buttonSet.registerButton(loadGameButton());
		m_buttonSet.registerButton(exitGameButton());
		m_buttonSet.setSelectedButton(loadGameButton().getName());

		m_buttonSet.setOnClickFunc(newGameButton().getName(), []() { Print << U"NewGame�{�^���������ꂽ"; });
		m_buttonSet.setOnClickFunc(loadGameButton().getName(), []() { Print << U"LoadGame�{�^���������ꂽ"; });
		m_buttonSet.setOnClickFunc(exitGameButton().getName(), []() { Print << U"ExitGame�{�^���������ꂽ"; });
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
		// �J�[�\���̈ړ��̔䗦
		static const double CURSOR_MOVE_RATE = Config::get<double>(U"TitleScene.cursorMoveRate");

		// �J�[�\���̕��̕ύX
		internalDividingPoint
		(
			m_cursorWidth,
			buttonSize().x,
			CURSOR_MOVE_RATE
		);

		// �J�[�\���̉��ɏo����̒����̕ύX
		internalDividingPoint
		(
			m_cursorLineLength,
			Scene::Width(),
			CURSOR_MOVE_RATE
		);

		// �J�[�\���̉��ɏo����̕s�����x�̕ύX
		internalDividingPoint
		(
			m_cursorLineAlpha,
			0,
			CURSOR_MOVE_RATE
		);
	}

	void TitleScene::draw() const
	{
		Scene::Rect().draw(MyBlack);

		drawLogo();

		drawButton();
	}

	void TitleScene::drawLogo() const
	{
		// ���S��`�悷����W
		static const Point LOGO_POS = Config::get<Point>(U"TitleScene.logoPos");
		// �V�t�g�̕p�x
		static const double SHIFT_FREQUENCY = Config::get<double>(U"TitleScene.shiftFrequency");
		// �V�t�g�̗�
		static const double SHIFT_LENGTH = Config::get<double>(U"TitleScene.shiftLength");

		{
			// �萔�o�b�t�@�̐ݒ�
			ConstantBuffer<Shift> cb;
			cb->g_rShift = makeShift(SHIFT_FREQUENCY, SHIFT_LENGTH);
			cb->g_gShift = makeShift(SHIFT_FREQUENCY, SHIFT_LENGTH);
			cb->g_bShift = makeShift(SHIFT_FREQUENCY, SHIFT_LENGTH);
			Graphics2D::SetConstantBuffer(ShaderStage::Pixel, 1, cb);

			// �V�F�[�_�̊J�n
			ScopedCustomShader2D shader(MyPixelShader::get(U"TitleLogo"));

			// ���S�̕`��
			TextureAsset(U"Logo").drawAt(LOGO_POS);
		}
	}

	void TitleScene::drawButton() const
	{
		// �J�[�\���̕`��
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

		// �{�^���̕`��
		for (const auto& button : m_buttonSet.getButtonList())
		{
			Color color = (button.first == m_buttonSet.getSelectedButton().getName())
				? MyBlack
				: MyWhite;

			FontAsset(U"20")(button.first)
				.drawAt(button.second.getRegion().center(), color);
		}
	}

	Float2 TitleScene::makeShift(double frequency, double shift)
	{
		return randomFrequency(frequency)
			? Float2(Random(-shift, shift), Random(-shift, shift))
			: Float2::Zero();
	}
}