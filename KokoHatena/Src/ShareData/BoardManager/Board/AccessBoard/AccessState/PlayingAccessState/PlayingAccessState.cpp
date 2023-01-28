#include "PlayingAccessState.hpp"

namespace Kokoha
{
	void PlayingAccessState::input(const Vec2&)
	{
	}

	Optional<std::shared_ptr<AccessState>> PlayingAccessState::update(
		AccessObject::GuidToObject& objectMap,
		AccessObject::TypeToGuidSet& typeToGuidSet)
	{
		// �v���C���[�̍��W�̎擾
		Circle playerBody = Circle(-1e5, -1e5, 0); // ���I�u�W�F�N�g�ƐڐG���Ȃ����W�ŏ�����
		for (const auto& guid : typeToGuidSet[AccessObject::Type::PLAYER])
		{
			playerBody = objectMap[guid]->body();
		}
		
		// �v���C���[���G�ƐڐG
		for (const auto& guid : typeToGuidSet[AccessObject::Type::ENEMY])
		{
			if (playerBody.intersects(objectMap[guid]->body()))
			{
				// TODO: FailedAccessState�ɑJ��
			}
		}

		// �v���C���[���S�[���ƐڐG
		for (const auto& guid : typeToGuidSet[AccessObject::Type::GOAL])
		{
			if (playerBody.intersects(objectMap[guid]->body()))
			{
				// TODO: SuccessAccessState�ɑJ��
			}
		}

		return none;
	}

	bool PlayingAccessState::isUpdatingObject() const
	{
		return true;
	}

	void PlayingAccessState::draw() const
	{
	}
}