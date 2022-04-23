
#include"Config/Config.hpp"

void Main()
{
	// ウィンドウの設定
	Window::Resize(Kokoha::Config::get<Size>(U"Window.size"));
	Window::SetTitle(Kokoha::Config::get<String>(U"Window.name"));

	while (System::Update())
	{
	}
}