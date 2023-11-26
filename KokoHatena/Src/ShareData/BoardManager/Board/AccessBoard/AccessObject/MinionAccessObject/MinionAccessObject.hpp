#pragma once

#include "../AccessObject.hpp"

namespace Kokoha
{
	class MinionAccessObject : public AccessObject
	{
	protected:

		// 目的地
		Vec2 m_goal;

	private:

		// 光の面積
		double m_lightArea;

		// Trackを作成する時間
		double m_trackTime;

	public:

		MinionAccessObject(const Vec2& pos, double lightArea);

	private:

		void update(const Terrain& terrain) override;

		void draw() const override;

		void checkOthers(
			const Terrain& terrain,
			const GuidToObject& guidToObject,
			const TypeToGuidSet& typeToGuidSet
		) override;

	protected:

		/// <summary>
		/// 目的地の設定を行うための関数
		/// overrideして使う
		/// </summary>
		/// <param name="terrain"> 地形 </param>
		/// <param name="guidToObject"> guidからオブジェクトへの連想配列 </param>
		/// <param name="typeToGuidSet"> オブジェクトの種類からguidへの連想配列 </param>
		virtual void setGoal(
			const Terrain& terrain,
			const GuidToObject& guidToObject,
			const TypeToGuidSet& typeToGuidSet
		) = 0;

		/// <summary>
		/// 光の面積の最大値（初期値）
		/// </summary>
		virtual double maxLightArea() const = 0;
	};
}
