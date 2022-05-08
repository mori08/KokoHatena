#pragma once

#include<future>
#include"../Scene.hpp"

namespace Kokoha
{
	class LoadScene : public MyApp::Scene
	{
	private:

		std::future<SceneName> m_loadThread;

	public:

		LoadScene(const InitData& init, std::function<SceneName()> loadFunc);

		/// <remarks>
		/// このコンストラクタを使用する場合
		/// 必ずsetLoadThreadで関数を設定すること
		/// </remarks>
		LoadScene(const InitData& init);

		virtual ~LoadScene();

	private:

		void update() override;

		virtual void draw() const override;

		void drawFadeIn(double) const override;

		void drawFadeOut(double) const override;

	protected:

		/// <summary>
		/// スレッドに関数の設定
		/// </summary>
		/// <param name="loadFunc"> 関数 </param>
		void setLoadThread(std::function<SceneName()> loadFunc);

	};
}