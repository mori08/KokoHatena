#pragma once

#include "../EnemyAccessObject/EnemyAccessObject.hpp"
#include "../../../../../../MyLibrary/SliceTexture/SliceTexture.hpp"

namespace Kokoha
{
	/// <summary>
	/// 敵オブジェクトを生成する敵オブジェクト
	/// （他の敵オブジェクトの基底クラスとしても使う）
	/// </summary>
	class HoleAccessObject : public EnemyAccessObject
	{
	private:

		// オブジェクト生成時間(s)
		double m_makingObjectTime = 0;

		// 生成したオブジェクトのguidの集合
		std::list<String> m_enemyGuidList;

	public:

		HoleAccessObject(const Vec2& pos);

	protected:

		virtual void update(const Terrain& terrain) override;

		virtual Vec2 getTargetPos();

		void makeEnemy();

		virtual void checkOthers(const Terrain& terrain, const GuidToObject& guidToObject, const TypeToGuidSet& typeToGuidSet) override;

	};
}
