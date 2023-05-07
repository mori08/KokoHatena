#include "PlayingAccessState.hpp"
#include "../FailedAccessState/FailedAccessState.hpp"
#include "../SuccessAccessState/SuccessAccessState.hpp"
#include "../../AccessObject/MinionAccessObject/MinionAccessObject.hpp"

namespace Kokoha
{
	void PlayingAccessState::input(const Vec2& cursorPos)
	{
		m_isMakingMinion = MouseL.down() && boardRect().contains(cursorPos);
	}

	Optional<std::shared_ptr<AccessState>> PlayingAccessState::update(
		AccessObject::GuidToObject& objectMap,
		AccessObject::TypeToGuidSet& typeToGuidSet,
		BoardRequest&)
	{
		// �v���C���[�̍��W�̎擾
		Circle playerBody = Circle(-1e5, -1e5, 0); // ���I�u�W�F�N�g�ƐڐG���Ȃ����W�ŏ�����
		for (const auto& guid : typeToGuidSet[AccessObject::Type::PLAYER])
		{
			playerBody = objectMap[guid]->body();
		}
		
		// MinionAccessObject�̍쐬
		if (m_isMakingMinion)
		{
			AccessObject::Ptr ptr = std::make_shared<MinionAccessObject>(playerBody.center);
			AccessObject::setMakingObject(ptr, objectMap, typeToGuidSet);
		}
		m_isMakingMinion = false;

		// �v���C���[���G�ƐڐG
		for (const auto& guid : typeToGuidSet[AccessObject::Type::ENEMY])
		{
			if (playerBody.intersects(objectMap[guid]->body()))
			{
				std::shared_ptr<AccessState> rtn = std::make_shared<FailedAccessState>(Terrain::toSquare(playerBody.center));
				return rtn;
			}
		}

		// �v���C���[���S�[���ƐڐG
		for (const auto& guid : typeToGuidSet[AccessObject::Type::GOAL])
		{
			if (playerBody.intersects(objectMap[guid]->body()))
			{
				std::shared_ptr<AccessState> rtn = std::make_shared<SuccessAccessState>(playerBody.center);
				return rtn;
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