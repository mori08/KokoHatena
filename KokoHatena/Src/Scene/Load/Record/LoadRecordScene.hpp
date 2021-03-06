#pragma once


#include "../LoadScene.hpp"
#include "../../../SliceTexture/SliceTexture.hpp"


namespace Kokoha
{
	/// <summary>
	/// LoadRecordSceneクラス
	/// RecordManagerにRecordを読み込む
	/// </summary>
	class LoadRecordScene : public LoadScene
	{
	private:

	public:

		LoadRecordScene(const InitData init);

	private:

		void subUpdate() override;

		void draw() const override;

	};
}