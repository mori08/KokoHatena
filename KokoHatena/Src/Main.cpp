#include"MyLibrary/MyLibrary.hpp"
#include"MyPixelShader/MyPixelShader.hpp"
#include"Config/Config.hpp"

#include"Scene/TitleScene/TitleScene.hpp"
#include"Scene/DesktopScene/DesktopScene.hpp"
#include"Scene/LoadScene/LoadRecordScene/LoadRecordScene.hpp"
#include"Scene/LoadScene/LoadBoardScene/LoadBoardScene.hpp"
#include"Scene/LoadScene/SaveRecordScene/SaveRecordScene.hpp"
#include"Scene/SelectRecordScene/SelectRecordScene.hpp"
#include"Scene/LastBattleScene/LastBattleScene.hpp"
#include"Scene/EndingScene/EndingScene.hpp"

using namespace Kokoha;

void Main()
{
	// ウィンドウの設定
	//Window::Resize(Config::get<Size>(U"Window.size"));
	Window::SetTitle(Config::get<String>(U"Window.name"));

	// 描画設定
	Scene::SetBackground(MyBlack);

	// リソース管理
#ifdef _DEBUG
	TextWriter rc(U"addResource");
	TextWriter ast(U"asset/list");
	registerResource(U"asset/", rc, ast);
	rc.close();
	ast.close();
#endif // _DEBUG

	// アセット管理
	registerAsset(U"asset/");
	MyPixelShader::loadPixelShader();
	for (int32 i = 10; i <= 40; ++i)
	{
		FontAsset::Register(ToString(i), i, Typeface::Medium);
	}

	// シーン
	MyApp sceneManager;
	sceneManager.add<TitleScene>(SceneName::TITLE);
	sceneManager.add<DesktopScene>(SceneName::DESKTOP);
	sceneManager.add<LoadRecordScene>(SceneName::LOAD_RECORD);
	sceneManager.add<LoadBoardScene>(SceneName::LOAD_BOARD);
	sceneManager.add<SaveRecordScene>(SceneName::SAVE_RECORD);
	sceneManager.add<SelectLoadRecordScene>(SceneName::SELECT_LOAD_RECORD);
	sceneManager.add<SelectSaveRecordScene>(SceneName::SELECT_SAVE_RECORD);
	sceneManager.add<LastBattleScene>(SceneName::LAST_BATTLE);
	sceneManager.add<EndingScene>(SceneName::ENDING);
	sceneManager.setFadeColor(MyBlack);

	while (System::Update())
	{
		sceneManager.update();

		showFPS();
	}
}
