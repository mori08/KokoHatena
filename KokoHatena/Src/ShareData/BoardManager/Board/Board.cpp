#include "Board.hpp"
#include "../../../Config/Config.hpp"
#include "../../../MyLibrary/MyLibrary.hpp"

namespace 
{
	/// <summary>
	/// フレーム上部の操作盤の高さ
	/// </summary>
	int32 controlFrameHeight()
	{
		static const int32 CONTROL_FRAME_HEIGHT = Kokoha::Config::get<int32>(U"Board.controlFrameHeight");
		return CONTROL_FRAME_HEIGHT;
	}
}

namespace Kokoha
{
	Board::Board(const Role& role, const String& configName, const State& state)
		: m_role(role)
		, m_state(state)
		, m_name(Config::get<String>(configName + U".name"))
		, m_size(Config::get<Size>  (configName + U".size"))
		, m_pos(Scene::Center() - m_size/2) // 画面中心に表示
		, m_render(m_size)
		, m_iconTextureName(configName)
		, m_iconOrder(Config::get<int32>(configName + U".iconOrder") )
	{
	}


	bool Board::onIconClicked() const
	{
		return m_state != State::NONE
			&& m_iconOrder >= 0
			&& getIconRect().leftClicked();
	}

	bool Board::mouseLeftDown() const
	{
		return m_state == State::IS_DISPLAYED
			&& Rect(m_pos, m_size + Point::Down(controlFrameHeight())).leftClicked()
			&& Cursor::Pos().y < Scene::Height() - getIconRect().h;
	}

	void Board::drawIcon() const
	{
		if (m_iconOrder < 0 || m_state == State::NONE) { return; }

		const Rect iconRect = getIconRect();
		
		TextureAsset(m_iconTextureName)
			(0, (m_state == State::IS_DISPLAYED) * iconRect.h, iconRect.size)
			.drawAt(iconRect.center());
	}


	Board::BoardRequest Board::input()
	{
		if (hideButtonRect().movedBy(m_pos).leftClicked())
		{
			return makeRequest(m_role, U"hide");
		}
			
		movePosByCursor();

		return inputInBoard();
	}

	void Board::update()
	{
		if (m_state != State::IS_DISPLAYED) { return; }

		updateInBoard();
	}

	void Board::draw() const
	{
		if (m_state != State::IS_DISPLAYED) { return; }

		// フレームの太さ
		static const double FRAME_THICKNESS = Config::get<double>(U"Board.frameThickness");
		// 名前を描画する座標
		static const Point NAME_POS = Config::get<Point>(U"Board.namePos");

		// レンダーテクスチャーのクリア
		m_render.clear(MyBlack);

		// レンダーテクスチャーを使って Rect(m_pos + Point::Down(controlFrameHeight()), m_size) に描画
		{
			ScopedRenderTarget2D target(m_render);

			// ボード内の描画
			drawInBoard();
		}
		Graphics2D::Flush();
		m_render.resolve();
		m_render.draw(m_pos + Point::Down(controlFrameHeight()));

		// フレームの描画
		Rect(m_pos, m_size + Point::Down(controlFrameHeight())).drawFrame(FRAME_THICKNESS, 0, MyWhite);
		// フレーム上部の操作盤
		Rect(m_pos, m_size.x, controlFrameHeight()).draw(MyWhite);
		TextureAsset(U"Small" + m_iconTextureName).draw(m_pos);
		TextureAsset(U"HideButton").draw(m_pos + hideButtonRect().pos);
		FontAsset(U"15")(m_name).draw(m_pos + NAME_POS, MyBlack);
	}

	Vec2 Board::cursorPosFInBoard() const
	{
		return Cursor::PosF() - m_pos - Point::Down(controlFrameHeight());
	}

	void Board::movePosByCursor()
	{
		if (MouseL.up())
		{
			m_optMovePos = none;
			return;
		}

		if (Rect(m_pos, m_size.x, controlFrameHeight()).leftClicked())
		{
			m_optMovePos = Cursor::Pos() - m_pos;
		}

		if (!m_optMovePos) { return; }

		m_pos = Cursor::Pos() - m_optMovePos.value();
		m_pos.x = Clamp(m_pos.x, 0, Scene::Size().x - m_size.x);
		m_pos.y = Clamp(m_pos.y, 0, Scene::Size().y - m_size.y);
	}

	const Rect Board::getIconRect() const
	{
		// アイコンのサイズ
		static const Size iconSize = Config::get<Size>(U"Board.iconSize");

		return Rect(
			m_iconOrder * iconSize.x,
			Scene::Height() - iconSize.y,
			iconSize
		);
	}

	const Rect Board::hideButtonRect() const
	{
		// アイコンのサイズ
		static const Size buttonSize = Config::get<Size>(U"Board.hideButtonSize");

		return Rect(
			m_size.x - buttonSize.x,
			0,
			buttonSize
		);
	}
}