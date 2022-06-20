#pragma once

#include "../Scene.hpp"
#include "../../ShareData/BoardManager/Board.hpp"

namespace Kokoha
{
	/// <summary>
	/// Board�̃��X�g���Ǘ�����V�[��
	/// �Q�[���̃��C���̐i�s
	/// </summary>
	class DesktopScene : public MyApp::Scene
	{
	private:

		Board m_board;

	public:

		DesktopScene(const InitData& init);

	private:

		void update() override;

		void draw() const override;

	};
}