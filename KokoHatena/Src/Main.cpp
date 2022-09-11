#include"MyLibrary/MyLibrary.hpp"
#include"MyPixelShader/MyPixelShader.hpp"
#include"Config/Config.hpp"

#include"Scene/TitleScene/TitleScene.hpp"
#include"Scene/DesktopScene/DesktopScene.hpp"
#include"Scene/LoadScene/LoadRecordScene/LoadRecordScene.hpp"
#include"Scene/LoadScene/LoadBoardScene/LoadBoardScene.hpp"
#include"Scene/SelectRecordScene/SelectRecordScene.hpp"

using namespace Kokoha;

void Main()
{
	// ウィンドウの設定
	Window::Resize(Config::get<Size>(U"Window.size"));
	Window::SetTitle(Config::get<String>(U"Window.name"));

	// 描画設定
	Scene::SetBackground(MyBlack);

	// アセット管理
	registerAsset(U"asset/");
	Kokoha::MyPixelShader::loadPixelShader();
	for (int32 i = 10; i <= 40; ++i) 
	{
		FontAsset::Register(ToString(i), i, Typeface::Medium);
	}

	// シーン
	MyApp sceneManager;
	sceneManager.add<Kokoha::TitleScene>           (SceneName::TITLE);
	sceneManager.add<Kokoha::DesktopScene>         (SceneName::DESKTOP);
	sceneManager.add<Kokoha::LoadRecordScene>      (SceneName::LOAD_RECORD);
	sceneManager.add<Kokoha::LoadBoardScene>       (SceneName::LOAD_BOARD);
	sceneManager.add<Kokoha::SelectLoadRecordScene>(SceneName::SELECT_LOAD_RECORD);

	while (System::Update())
	{
		sceneManager.update();

		showFPS();
	}
}
