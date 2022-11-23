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

	public:

		/// <param name="point1"> 始点 </param>
		/// <param name="point2"> 終点 </param>
		PolarLine(const PolarPos& point1, const PolarPos& point2);

	public:

		/// <summary>
		/// ある角度となる直線上の動径
		/// </summary>
		/// <param name="a"> 角度 </param>
		/// <returns> 動径 </returns>
		Optional<double> r(double a) const;

	};
}