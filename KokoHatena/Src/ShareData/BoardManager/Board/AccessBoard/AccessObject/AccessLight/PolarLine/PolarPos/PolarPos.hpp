#pragma once

#include <Siv3D.hpp>

namespace Kokoha
{
	/// <summary>
	/// 極座標
	/// </summary>
	class PolarPos
	{
	public:

		// 偏角 in [-Pi,Pi]
		const double a;

		// 動径 in [0, Inf)
		const double r;

	public:

		/// <summary>
		/// 偏角と距離から極座標を作成
		/// </summary>
		/// <param name="angle"> 偏角 </param>
		/// <param name="distance"> 距離 </param>
		PolarPos(double angle, double distance);

		PolarPos(const PolarPos& another);

		/// <summary>
		/// 直交座標から変換
		/// </summary>
		/// <param name="pos"> 直交座標 </param>
		/// <param name="originPos"> r=0となる点の直交座標 </param>
		/// <param name="initalLineAngle"> 始線の角度 </param>
		PolarPos(const Vec2& pos, const Vec2& originPos, double initalLineAngle);

		

		/// <summary>
		/// 直交座標へ変換
		/// </summary>
		/// <param name="originPos"> r=0となる点の直交座標 </param>
		/// <param name="initialLineAngle"> 始線の角度 </param>
		/// <returns> 直交座標 </returns>
		Vec2 toOrthoPos(const Vec2& originPos, double initialLineAngle) const;

	};
}