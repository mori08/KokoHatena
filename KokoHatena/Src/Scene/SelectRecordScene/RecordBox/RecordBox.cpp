#include "RecordBox.hpp"
#include "../../../Config/Config.hpp"
#include "../../../MyLibrary/MyLibrary.hpp"

namespace Kokoha
{
	RecordBox::RecordBox(std::function<void()> onSelected, const std::pair<String, String>& textPair)
		: m_onSelected(onSelected)
		, m_textPair(textPair)
	{
		// 画面内のRecordBoxの座標の一番上
		static const Point DRAW_POS = Config::get<Point>(U"SelectRecordScene.drawPos");
		m_pos.x = DRAW_POS.x;
		m_pos.y = Scene::Height();
	}

	void RecordBox::update()
	{
		// 座標の更新
		static const double MOVE_RATE_POS = Config::get<double>(U"RecordBox.posMoveRate");
		internalDividingPoint(m_pos, m_goal, MOVE_RATE_POS);

		if (m_pos.distanceFrom(m_goal) < 1e-5 && RectF(m_goal, getSize()).leftClicked())
		{
			m_onSelected();
		}
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
			setGoalPos(Vec2(DRAW_POS.x, -DRAW_SPACE - RecordBox::getSize().y));
			return;
		}

		const Vec2 pos = DRAW_POS + index * Vec2::Down(DRAW_SPACE + RecordBox::getSize().y);

		// 画面下側に隠す
		if (pos.y + getSize().y > Scene::Height())
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

	void RecordBox::draw() const
	{
		// m_textPair.firstを表示する座標
		static const Point TEXT_FIRST_POS = Config::get<Point>(U"RecordBox.textFirstPos");
		// m_textPair.seoncdを表示する座標
		static const Point TEXT_SECOND_POS = Config::get<Point>(U"RecordBox.textSecondPos");
		// 左右の枠の厚さ
		static const int32 FRAME_WIDTH = Config::get<int32>(U"RecordBox.frameWith");

		// m_textPairの描画
		FontAsset(U"20")(m_textPair.first ).draw(m_pos + TEXT_FIRST_POS );
		FontAsset(U"20")(m_textPair.second).draw(m_pos + TEXT_SECOND_POS);

		// 左側のフレーム
		RectF(
			m_pos + Point::Left(FRAME_WIDTH / 2),
			FRAME_WIDTH, getSize().y
		).draw(MyWhite);

		// 右側のフレーム
		RectF(
			m_pos + Point::Left(FRAME_WIDTH / 2 - getSize().x),
			FRAME_WIDTH, getSize().y
		).draw(MyWhite);
	}

	const Size& RecordBox::getSize()
	{
		// 描画するサイズ
		static const Size SIZE = Config::get<Size>(U"RecordBox.size");
		return SIZE;
	}
}