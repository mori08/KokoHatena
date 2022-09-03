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

	public:

		/// <summary>
		/// RecordBox��I������V�[��
		/// </summary>
		/// <param name="recordBox"> ��ԏ�ɕ\������RecordBox </param>
		/// <param name="recordFunc"> RecordSet�ɑΉ����鏈�� </param>
		/// <param name="explanation"> �V�[���̐����� </param>
		SelectRecordScene(
			const InitData& init, 
			const RecordBox& recordBox, 
			std::function<void(const RecordSet&)> recordFunc, 
			const String& explanation);

	protected:

		virtual void update() override;

		virtual void draw() const override;
	};

	/// <summary>
	/// ���[�h����RecordSet��o�^����
	/// </summary>
	class SelectLoadRecordScene : public SelectRecordScene
	{
	public:
		SelectLoadRecordScene(const InitData& init);
	};
}