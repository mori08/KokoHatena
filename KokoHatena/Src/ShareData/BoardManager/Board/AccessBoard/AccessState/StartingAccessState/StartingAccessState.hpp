#pragma once

#include "../AccessState.hpp"

namespace Kokoha
{
	/// <summary>
	/// �Q�[���J�n����AccessState
	/// </summary>
	class StartingAccessState : public AccessState
	{
	private:

		// 0 �̂Ƃ� ������h�炷
		int32 m_noiseCount;

		// �v���C���[�̂�����W
		Vec2 m_playerPos;

		// PlayingState�֑J�ڂ���Ƃ� true
		bool m_nextStateFlag;

		// �X�e�[�W��
		static String stageName;

		// ��������AccessObject�̃��X�g
		std::list<AccessObject::Ptr> m_makeObjectList;

	public:

		StartingAccessState(const String& argStageName);

		StartingAccessState();

	private:

		void input(const Vec2& cursorPos) override;

		Optional<std::shared_ptr<AccessState>> update(
			AccessObject::GuidToObject& objectMap,
			AccessObject::TypeToGuidSet& typeToGuidSet) override;

		bool isUpdatingObject() const override;

		void draw() const override;

		void setMakeObjectList();

	};
}