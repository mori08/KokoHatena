#include"MyLibrary/MyLibrary.hpp"
#include"Config/Config.hpp"

using namespace Kokoha;

void Main()
{
	// ウィンドウの設定
	Window::Resize(Config::get<Size>(U"Window.size"));
	Window::SetTitle(Config::get<String>(U"Window.name"));

	// アセット管理
	registerAsset(U"asset/");
	for (int32 i = 10; i <= 40; ++i) 
	{
		FontAsset::Register(ToString(i), i, Typeface::Medium);
	}

	while (System::Update())
	{
		showFPS();
	}
}