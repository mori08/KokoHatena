#include"LoadScene.hpp"
#include"../../Config/Config.hpp"
#include"../../MyLibrary/MyLibrary.hpp"

namespace
{
	bool debugMode()
	{
		const static bool rtn = Kokoha::Config::get<bool>(U"LoadScene.debugMode");
		return rtn;
	}
}

namespace Kokoha
{
	LoadScene::LoadScene(const InitData& init, std::function<SceneName()> loadFunc)
		: IScene(init)
	{
		if (debugMode)
		{
			nextSceneName = loadFunc();
		}
		else
		{
			// スレッドの開始
			m_loadThread = std::async(std::launch::async, loadFunc);
		}
	}


	LoadScene::LoadScene(const InitData& init)
		: IScene(init)
	{
	}


	LoadScene::~LoadScene()
	{
	}


	void LoadScene::update()
	{
		if (debugMode())
		{
			changeScene(nextSceneName);
			return;
		}

		// スレッドの状況の更新
		auto status = m_loadThread.wait_for(std::chrono::microseconds(0));

		// スレッドが終了していたらシーン遷移
		if (status != std::future_status::timeout)
		{
			auto sceneName = m_loadThread.get();

			if (!changeScene(sceneName)) { changeScene(SceneName::TITLE); }
		}
	}


	void LoadScene::draw() const
	{
		// 演出の円
		static const Circle LOADING_CIRCLE       = Config::get<Circle>(U"LoadScene.loadingCircle");
		// 演出の弧の太さ
		static const double LOADING_ARC_THICNESS = Config::get<double>(U"LoadScene.loadingArcThicness");
		// 演出の弧の長さ
		static const double LOADING_ARC_LENGTH   = Config::get<double>(U"LoadScene.loadingArcLength");
		// 小さな円の個数
		static const int32  SMALL_CIRCLE_NUM     = Config::get<int32 >(U"LoadScene.smallCircleNum");
		// テキストを表示する座標
		static const Point  TEXT_POS             = Config::get<Point >(U"LoadScene.textPos");
		// Loadingの後につける . の数の最大値
		static const int32  MAX_DOT_NUM          = Config::get<int32 >(U"LoadScene.maxDotNum");

		for (int32 i = 0; i < SMALL_CIRCLE_NUM; ++i)
		{
			double a = Math::TwoPi * i / SMALL_CIRCLE_NUM - Scene::Time();
			Circle
			(
				LOADING_CIRCLE.center + LOADING_CIRCLE.r * Vec2(Cos(a), Sin(a)),
				LOADING_ARC_THICNESS
			).draw(Color(MyWhite, 0xA0));
		}
		LOADING_CIRCLE.drawArc(Scene::Time(), LOADING_ARC_LENGTH, LOADING_ARC_THICNESS, LOADING_ARC_THICNESS, MyWhite);
		FontAsset(U"20")(U"Loading" + String(U"...").substr(0, (int32)Scene::Time() % MAX_DOT_NUM)).draw(TEXT_POS);
	}


	void LoadScene::drawFadeIn(double) const
	{
		draw();
	}


	void LoadScene::drawFadeOut(double) const
	{
		draw();
	}


	void LoadScene::setLoadThread(std::function<SceneName()> loadFunc)
	{
		if (debugMode())
		{
			nextSceneName = loadFunc();
		}
		else
		{
			// スレッドの開始
			m_loadThread = std::async(std::launch::async, loadFunc);
		}
	}
}
