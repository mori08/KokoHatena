#pragma once

#include"../Scene.hpp"

namespace Kokoha
{
	/// <summary>
	/// Board�̃��X�g���Ǘ�����V�[��
	/// �Q�[���̃��C���̐i�s
	/// </summary>
	class DesktopScene : public MyApp::Scene
	{
	private:

	public:

		DesktopScene(const InitData& init);

	private:

		void update() override;

		void draw() const override;

	};
}