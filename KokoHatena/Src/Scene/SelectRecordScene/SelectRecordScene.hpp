#pragma once

#include "../Scene.hpp"

namespace Kokoha
{
	/// <summary>
	/// RecordSet��I������V�[��
	/// �I������RecordSet���ǂ����邩�͔h���N���X�Ō��肷��
	/// </summary>
	class SelectRecordScene : public MyApp::Scene
	{
	private:

	public:

		SelectRecordScene(const InitData& init);

		void update() override;

		void draw() const override;

	};
}