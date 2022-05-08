#include"LoadScene.hpp"
#include"../../Config/Config.hpp"
#include"../../MyLibrary/MyLibrary.hpp"

namespace Kokoha
{
	LoadScene::LoadScene(const InitData& init, std::function<SceneName()> loadFunc)
		: IScene(init)
	{
		// �X���b�h�̊J�n
		m_loadThread = std::async(std::launch::async, loadFunc);
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
		// �X���b�h�̏󋵂̍X�V
		auto status = m_loadThread.wait_for(std::chrono::microseconds(0));

		// �X���b�h���I�����Ă�����V�[���J��
		if (status != std::future_status::timeout)
		{
			auto sceneName = m_loadThread.get();

			if (!changeScene(sceneName)) { changeScene(SceneName::TITLE); }
		}
	}


	void LoadScene::draw() const
	{
		// ���o�̉~
		static const Circle LOADING_CIRCLE       = Config::get<Circle>(U"LoadScene.loadingCircle");
		// ���o�̌ʂ̑���
		static const double LOADING_ARC_THICNESS = Config::get<double>(U"LoadScene.loadingArcThicness");
		// ���o�̌ʂ̒���
		static const double LOADING_ARC_LENGTH   = Config::get<double>(U"LoadScene.loadingArcLength");
		// �����ȉ~�̌�
		static const int32  SMALL_CIRCLE_NUM     = Config::get<int32 >(U"LoadScene.smallCircleNum");
		// �e�L�X�g��\��������W
		static const Point  TEXT_POS             = Config::get<Point >(U"LoadScene.textPos");
		// Loading�̌�ɂ��� . �̐��̍ő�l
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
		// �X���b�h�̊J�n
		m_loadThread = std::async(std::launch::async, loadFunc);
	}
}