#pragma once

#include "../EnemyAccessObject/EnemyAccessObject.hpp"
#include "../../../../../../MyLibrary/SliceTexture/SliceTexture.hpp"
#include "../../../../../../Config/Config.hpp"

namespace Kokoha
{
	/// <summary>
	/// 敵オブジェクトを生成する敵オブジェクト
	/// </summary>
	template<typename EnemyType>
	class HoleAccessObject : public EnemyAccessObject
	{
	private:

		// オブジェクト生成時間(s)
		double m_makingObjectTime = Inf<double>;

		// 生成したオブジェクトのguidの集合
		std::list<String> m_enemyGuidList;

	public:

		HoleAccessObject(const Vec2& pos)
			: EnemyAccessObject(pos, U"HoleAccessObject")
		{
		}

	protected:

		virtual Ptr makeEnemy()
		{
			return std::make_shared<EnemyType>(body().center);
		}

		virtual void checkOthers(const Terrain& terrain, const GuidToObject& guidToObject, const TypeToGuidSet& typeToGuidSet) override
		{
			Erase_if(
				m_enemyGuidList,
				[&guidToObject](const String& guid) { return !guidToObject.count(guid); }
			);

			// 生成する敵数の制限
			static const size_t ENEMY_SIZE_LIMIT = Config::get<size_t>(U"HoleAccessObject.enemySizeLimit");
			// 作成時間
			static const double ENEMY_MAKE_TIME = Config::get<double>(U"HoleAccessObject.enemyMakeTime");
			m_makingObjectTime += Scene::DeltaTime();
			if (m_enemyGuidList.size() < ENEMY_SIZE_LIMIT && m_makingObjectTime > ENEMY_MAKE_TIME)
			{
				m_makingObjectTime = 0;
				Ptr ptr = makeEnemy();
				m_enemyGuidList.emplace_back(ptr->guid());
				makeObject(std::move(ptr));
			}

			EnemyAccessObject::checkOthers(terrain, guidToObject, typeToGuidSet);
		}
	};
}
