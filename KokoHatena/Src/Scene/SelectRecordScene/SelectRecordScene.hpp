#pragma once

#include "../Scene.hpp"

namespace Kokoha
{
	/// <summary>
	/// RecordSetを選択するシーン
	/// 選択したRecordSetをどうするかは派生クラスで決定する
	/// </summary>
	class SelectRecordScene : public MyApp::Scene
	{
	private:

	public:

		SelectRecordScene(const InitData& init);

		void update() override;

		void draw() const override;

	};
}