#include"MyLibrary/MyLibrary.hpp"
#include"MyPixelShader/MyPixelShader.hpp"
#include"Config/Config.hpp"

#include"Scene/TitleScene/TitleScene.hpp"
#include"Scene/LoadScene/LoadRecordScene/LoadRecordScene.hpp"
#include"Scene/DesktopScene/DesktopScene.hpp"

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
	sceneManager.add<Kokoha::TitleScene>     (SceneName::TITLE);
	sceneManager.add<Kokoha::LoadRecordScene>(SceneName::LOAD);
	sceneManager.add<Kokoha::DesktopScene>   (SceneName::DESKTOP);

	while (System::Update())
	{
		sceneManager.update();

		showFPS();
	}
}
