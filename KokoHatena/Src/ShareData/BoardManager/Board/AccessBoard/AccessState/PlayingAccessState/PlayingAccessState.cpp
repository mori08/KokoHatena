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
				// TODO: FailedAccessStateに遷移
			}
		}

		// プレイヤーがゴールと接触
		for (const auto& guid : typeToGuidSet[AccessObject::Type::GOAL])
		{
			if (playerBody.intersects(objectMap[guid]->body()))
			{
				// TODO: SuccessAccessStateに遷移
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