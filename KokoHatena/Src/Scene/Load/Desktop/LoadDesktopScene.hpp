#pragma once


#include "../LoadScene.hpp"
#include "../../../SliceTexture/SliceTexture.hpp"


namespace Kokoha
{
	/// <summary>
	/// LoadDesktopSceneクラス
	/// Recordの内容に応じてboardShareDataを初期化
	/// </summary>
	class LoadDesktopScene : public LoadScene
	{
	private:

		SliceTexture m_boardLogo;

	public:

		LoadDesktopScene(const InitData& init);

	private:

		void subUpdate() override;

		void draw() const override;

	};
}