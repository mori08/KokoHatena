#pragma once

#include "PolarPos/PolarPos.hpp"

namespace Kokoha
{
	/// <summary>
	/// 2点の極座標でなる線分
	/// </summary>
	class PolarLine
	{
	public:

		// 始点
		const PolarPos p1;

		// 終点
		const PolarPos p2;

	private:

		// ACos(a)+BSin(a) = C/r

		// 直線 Ax+By=C
		const double A;

		// 直線 Ax+By=C
		const double B;

		// 直線 Ax+By=C
		const double C;

	public:

		/// <param name="point1"> 始点 </param>
		/// <param name="point2"> 終点 </param>
		PolarLine(const PolarPos& point1, const PolarPos& point2);

	public:

		/// <summary>
		/// 光源から指定の角度となる直線上の動径
		/// </summary>
		/// <param name="a"> 角度 </param>
		/// <returns> 動径 , 指定の角度となる点がない場合 none </returns>
		Optional<double> r(double a) const;

		/// <summary>
		/// 光源から指定の距離となる直線上の偏角
		/// </summary>
		/// <param name="r"> 距離 </param>
		/// <returns> 偏角 , 0 ~ 2個 </returns>
		std::list<double> a(double r) const;

		/// <summary>
		/// 半径rの円と共有部分を持つか
		/// </summary>
		/// <param name="r"> 半径 </param>
		/// <returns> true の場合共有を持つ </returns>
		bool on(double r) const;

	};
}