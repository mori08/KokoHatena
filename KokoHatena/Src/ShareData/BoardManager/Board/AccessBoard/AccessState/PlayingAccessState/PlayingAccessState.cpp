#include "PlayingAccessState.hpp"
#include "../FailedAccessState/FailedAccessState.hpp"
#include "../SuccessAccessState/SuccessAccessState.hpp"
#include "../../AccessObject/MinionAccessObject/MinionAccessObject.hpp"
#include "../../../../../../Config/Config.hpp"

namespace Kokoha
{
	Optional<std::shared_ptr<AccessState>> PlayingAccessState::update(
		AccessObject::GuidToObject& objectMap,
		AccessObject::TypeToGuidSet& typeToGuidSet,
		BoardRequest&)
	{
		// プレイヤーの座標の取得
		Circle playerBody = Circle(-1e5, -1e5, 0); // 他オブジェクトと接触しない座標で初期化
		for (const auto& guid : typeToGuidSet[AccessObject::Type::PLAYER])
		{
			playerBody = objectMap[guid]->body();
		}

		// プレイヤーが敵と接触
		for (const auto& guid : typeToGuidSet[AccessObject::Type::ENEMY])
		{
			if (playerBody.intersects(objectMap[guid]->body()))
			{
				std::shared_ptr<AccessState> rtn = std::make_shared<FailedAccessState>(Terrain::toSquare(playerBody.center));
				return rtn;
			}
		}

		// プレイヤーがゴールと接触
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
