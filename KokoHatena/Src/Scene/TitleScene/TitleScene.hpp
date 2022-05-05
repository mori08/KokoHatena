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

	private:

		/// <summary>
		/// ���S�̕`��
		/// </summary>
		void drawLogo() const;

		/// <summary>
		/// �{�^���̕`��
		/// </summary>
		void drawButton() const;

		/// <summary>
		/// �V�F�[�_���Ɏg�p����V�t�g�̃x�N�g��
		/// </summary>
		/// <param name="frequency"> �p�x         </param>
		/// <param name="shift"    > ����̑傫�� </param>
		/// <returns> �V�t�g�̃x�N�g�� </returns>
		static Float2 makeShift(double frequency, double shift);

	};
}