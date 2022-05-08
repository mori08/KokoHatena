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
		/// ���̃R���X�g���N�^���g�p����ꍇ
		/// �K��setLoadThread�Ŋ֐���ݒ肷�邱��
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
		/// �X���b�h�Ɋ֐��̐ݒ�
		/// </summary>
		/// <param name="loadFunc"> �֐� </param>
		void setLoadThread(std::function<SceneName()> loadFunc);

	};
}