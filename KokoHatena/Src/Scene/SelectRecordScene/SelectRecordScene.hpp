#pragma once

#include "../Scene.hpp"
#include "RecordBox/RecordBox.hpp"

namespace Kokoha
{
	/// <summary>
	/// RecordBox��I������V�[��
	/// �I������RecordSet���ǂ����邩�͔h���N���X�Ō��肳���
	/// </summary>
	class SelectRecordScene : public MyApp::Scene
	{
	protected:

		// ���̃V�[���̐�����
		const String m_explanation;

		// RecordBox�̃��X�g
		std::list<RecordBox> m_recordBoxList;

		// ��ʓ��̈�ԏ�ɕ\������RecordBox�̃C�e���[�^
		std::list<RecordBox>::iterator m_topBoxItr;

		// RecordBox��I�������ꍇ�ɑJ�ڂ���V�[��
		const SceneName m_sceneName;

		// �X�N���[���o�[��\������y���W
		double m_scrollBarPosY;

		// �}�E�X�z�C�[���ł̃X�N���[�����̃N�[���^�C��
		double m_wheel;

	public:

		/// <summary>
		/// RecordBox��I������V�[��
		/// </summary>
		/// <param name="recordBox"> ��ԏ�ɕ\������RecordBox </param>
		/// <param name="recordFunc"> RecordSet�ɑΉ����鏈�� </param>
		/// <param name="explanation"> �V�[���̐����� </param>
		/// <param name="sceneName"> �I�����ɑJ�ڂ���V�[���� </param>
		SelectRecordScene(
			const InitData& init, 
			const RecordBox& recordBox, 
			std::function<void(RecordSet&)> recordFunc, 
			const String& explanation,
			SceneName sceneName
		);

	protected:

		virtual void update() override;

		virtual void draw() const override;

	private:

		/// <summary>
		/// �X�N���[���z�C�[���ł�RecordBox�̈ړ�
		/// </summary>
		void scrollWheel();

	};

	/// <summary>
	/// ���[�h����RecordSet��I������
	/// </summary>
	class SelectLoadRecordScene : public SelectRecordScene
	{
	public:
		SelectLoadRecordScene(const InitData& init);
	};

	/// <summary>
	/// �Z�[�u����RecordSet��I������
	/// </summary>
	class SelectSaveRecordScene : public SelectRecordScene
	{
	public:
		SelectSaveRecordScene(const InitData& init);
	};
}