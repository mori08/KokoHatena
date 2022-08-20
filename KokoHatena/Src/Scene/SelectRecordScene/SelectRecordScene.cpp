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

	}

	void SelectRecordScene::draw() const
	{
		// 描画する座標
		static const Point DRAW_POS = Config::get<Point>(U"SelectRecordScene.drawPos");

		static RecordSet recordSet = RecordSet().setRecordTime();

		recordSet.draw(DRAW_POS);
	}
}