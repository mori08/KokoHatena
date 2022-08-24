#pragma once

#include "../Scene.hpp"
#include "RecordBox/RecordBox.hpp"

namespace Kokoha
{
	/// <summary>
	/// RecordSet��I������V�[��
	/// �I������RecordSet���ǂ����邩�͔h���N���X�Ō��肷��
	/// </summary>
	class SelectRecordScene : public MyApp::Scene
	{
	protected:

		std::list<RecordBox> m_recordBoxList;

	public:

		SelectRecordScene(const InitData& init);

		virtual void update() override;

		virtual void draw() const override;

	protected:

		/// <summary>
		/// RecordBox��\��������W���擾����
		/// </summary>
		/// <param name="index"> RecordBox��\�����鏇�� </param>
		/// <returns> RecordBox��\��������W </returns>
		static Vec2 getRecordBoxPos(int32 index);

	};
}