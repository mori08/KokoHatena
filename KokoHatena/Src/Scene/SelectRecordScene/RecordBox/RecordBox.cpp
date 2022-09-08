#include "RecordBox.hpp"
#include "../../../Config/Config.hpp"
#include "../../../MyLibrary/MyLibrary.hpp"

namespace Kokoha
{
	/// <summary>
	/// 高さの取得
	/// </summary>
	int32 getHeight()
	{
		// 描画するサイズ
		static const int32 rtn = Config::get<int32>(U"RecordBox.height");
		return rtn;
	}

	/// <summary>
	/// 非表示中の幅の取得
	/// </summary>
	double getHideWidth()
	{
		// 描画するサイズ
		static const double rtn = Config::get<int32>(U"RecordBox.hideWidth");
		return rtn;
	}

	/// <summary>
	/// 表示中の幅の取得
	/// </summary>
	double getDisplayWidth()
	{
		// 描画するサイズ
		static const double rtn = Config::get<int32>(U"RecordBox.displayWidth");
		return rtn;
	}

	/// <summary>
	/// 選択中の幅の取得
	/// </summary>
	double getOverWidth()
	{
		// 描画するサイズ
		static const double rtn = Config::get<int32>(U"RecordBox.overWidth");
		return rtn;
	}

	/// <summary>
	/// 描画する範囲（サイズ）の取得
	/// </summary>
	/// <returns> 描画する範囲 </returns>
	double gethideWidth()
	{
		// 描画するサイズ
		static const int32 rtn = Config::get<int32>(U"RecordBox.hideWidth");
		return rtn;
	}

	/// <summary>
	/// 選択用のボタンの長方形
	/// </summary>
	/// <returns></returns>
	const RectF& getButtonRect()
	{
		static const RectF rtn = Config::get<RectF>(U"RecordBox.button");
		return rtn;
	}

	RecordBox::RecordBox(std::function<void()> onSelected, const std::pair<String, String>& textPair)
		: m_width(0)
		, m_onSelected(onSelected)
		, m_textPair(textPair)
	{
		// 画面内のRecordBoxの座標の一番上
		static const Point DRAW_POS = Config::get<Point>(U"SelectRecordScene.drawPos");

		m_pos.x = DRAW_POS.x;
		m_pos.y = Scene::Height();
	}

	bool RecordBox::update()
	{
		// 座標の更新
		static const double MOVE_RATE_POS = Config::get<double>(U"RecordBox.posMoveRate");
		internalDividingPoint(m_pos, m_goal, MOVE_RATE_POS);

		updateWidth();

		if (m_width > getButtonRect().tr().x && getButtonRect().movedBy(m_pos).leftClicked())
		{
			m_onSelected();
			return true;
		}

		return false;
	}

	void RecordBox::setGoalPos(const int32 index)
	{
		// 画面内のRecordBoxの座標の一番上
		static const Point DRAW_POS = Config::get<Point>(U"SelectRecordScene.drawPos");
		// RecordBoxの
		static const int32 DRAW_SPACE = Config::get<int32>(U"SelectRecordScene.recordBoxSpace");

		// 画面上側に隠す
		if (index < 0)
		{
			setGoalPos(Vec2(DRAW_POS.x, -DRAW_SPACE - getHeight()));
			return;
		}

		const Vec2 pos = DRAW_POS + index * Vec2::Down(DRAW_SPACE + getHeight());

		// 画面下側に隠す
		if (pos.y + getHeight() > Scene::Height())
		{
			setGoalPos(Vec2(DRAW_POS.x, Scene::Height() + DRAW_SPACE));
			return;
		}

		// 画面内に表示
		setGoalPos(pos);
	}

	void RecordBox::setGoalPos(const Vec2& pos)
	{
		m_goal = pos;
	}

	void RecordBox::draw(int32 index) const
	{
		// 番号を表示する座標
		static const Point TEXT_FILE_POS = Config::get<Point>(U"RecordBox.textFilePos");
		// m_textPair.firstを表示する座標
		static const Point TEXT_FIRST_POS = Config::get<Point>(U"RecordBox.textFirstPos");
		// m_textPair.seoncdを表示する座標
		static const Point TEXT_SECOND_POS = Config::get<Point>(U"RecordBox.textSecondPos");
		// 左右の枠の厚さ
		static const double FRAME_WIDTH = Config::get<int32>(U"RecordBox.frameWith");
		// 背景に描画する座標
		static const ColorF BACK_COLOR = Config::get<ColorF>(U"RecordBox.backColor");

		// 背景
		RectF(m_pos, m_width, getHeight()).draw(BACK_COLOR);

		// テキスト
		FontAsset(U"18")(U"File " + ToString(index)).draw(m_pos + TEXT_FILE_POS);
		FontAsset(U"12")(m_textPair.first ).draw(m_pos + TEXT_FIRST_POS );
		FontAsset(U"20")(m_textPair.second).draw(m_pos + TEXT_SECOND_POS);

		// ボタン
		const Rect button = getButtonRect().movedBy(m_pos).draw(MyBlack);
		button.draw(MyBlack);
		if (m_width > getButtonRect().tr().x && button.mouseOver())
		{
			static const RectF buttonLight = Config::get<RectF>(U"RecordBox.buttonLight");
			buttonLight.movedBy(m_pos).draw(BACK_COLOR);
		}

		// 左側を隠す
		RectF(m_pos + Vec2::Right(m_width), getOverWidth(), getHeight()).draw(MyBlack);

		// 左側のフレーム
		RectF(
			m_pos + Vec2::Left(FRAME_WIDTH / 2),
			FRAME_WIDTH, getHeight()
		).draw(MyWhite);

		// 右側のフレーム
		RectF(
			m_pos + Vec2::Left(FRAME_WIDTH / 2 - m_width),
			FRAME_WIDTH, getHeight()
		).draw(MyWhite);
	}

	void RecordBox::updateWidth()
	{
		double goalWidth = 0;

		// 画面外
		if (m_goal.y < 0 || m_goal.y > Scene::Height())
		{
			goalWidth = getHideWidth();
		}

		// マウスをオーバーしている
		else if (RectF(m_goal, m_width, getHeight()).mouseOver())
		{
			goalWidth = getOverWidth();
		}

		// 画面内
		else
		{
			goalWidth = getDisplayWidth();
		}

		// 幅の更新
		static const double MOVE_RATE_POS = Config::get<double>(U"RecordBox.posMoveRate");
		internalDividingPoint(m_width, goalWidth, MOVE_RATE_POS);
	}
}