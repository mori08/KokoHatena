#pragma once

#include "../Scene.hpp"
#include "../../ButtonSet/ButtonSet.hpp"

namespace Kokoha
{
	/// <summary>
	/// �^�C�g���V�[��
	/// </summary>
	class TitleScene : public MyApp::Scene
	{
	private:

		// �{�^���̊Ǘ�
		ButtonSet m_buttonSet;

		// �J�[�\���̕�
		double m_cursorWidth;

		// �J�[�\���̉��ɏo����̒���
		double m_cursorLineLength;

		// �J�[�\���̉��ɏo����̕s�����x
		double m_cursorLineAlpha;

	public:

		TitleScene(const InitData& init);

		void update() override;

		void updateFadeOut(double) override;

		void draw() const override;

	};
}