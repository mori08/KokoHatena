#pragma once

#include "../Scene.hpp"
#include "RecordBox/RecordBox.hpp"

namespace Kokoha
{
	/// <summary>
	/// RecordSetを選択するシーン
	/// 選択したRecordSetをどうするかは派生クラスで決定する
	/// </summary>
	class SelectRecordScene : public MyApp::Scene
	{
	protected:

		std::list<RecordBox> m_recordBoxList;

	public:

		SelectRecordScene(const InitData& init);

		virtual void update() override;

		virtual void draw() const override;

	protected:

		/// <summary>
		/// RecordBoxを表示する座標を取得する
		/// </summary>
		/// <param name="index"> RecordBoxを表示する順序 </param>
		/// <returns> RecordBoxを表示する座標 </returns>
		static Vec2 getRecordBoxPos(int32 index);

	};
}