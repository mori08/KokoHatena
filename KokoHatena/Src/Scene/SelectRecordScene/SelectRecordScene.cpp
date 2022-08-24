#include "SelectRecordScene.hpp"
#include "../../Config/Config.hpp"

namespace Kokoha
{
	SelectRecordScene::SelectRecordScene(const InitData& init)
		: IScene(init)
	{
	}

	void SelectRecordScene::update()
	{
		for (auto& recordBox : m_recordBoxList)
		{
			recordBox.update();
		}
	}

	void SelectRecordScene::draw() const
	{		
		for (const auto& recordBox : m_recordBoxList)
		{
			recordBox.draw();
		}
	}

	Vec2 SelectRecordScene::getRecordBoxPos(int32 index)
	{
		// ï`âÊÇ∑ÇÈç¿ïW
		static const Point DRAW_POS = Config::get<Point>(U"SelectRecordScene.drawPos");
		// RecordBoxÇÃ
		static const int32 DRAW_SPACE = Config::get<int32>(U"SelectRecordScene.recordBoxSpace");
		
		return DRAW_POS + index * Vec2::Down(DRAW_SPACE + RecordBox::getSize().y);
	}
}