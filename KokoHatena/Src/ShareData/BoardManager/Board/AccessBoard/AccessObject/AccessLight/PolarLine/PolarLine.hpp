#pragma once

#include "PolarPos/PolarPos.hpp"

namespace Kokoha
{
	/// <summary>
	/// 2�_�̋ɍ��W�łȂ����
	/// </summary>
	class PolarLine
	{
	public:

		// �n�_
		const PolarPos p1;

		// �I�_
		const PolarPos p2;

	public:

		/// <param name="point1"> �n�_ </param>
		/// <param name="point2"> �I�_ </param>
		PolarLine(const PolarPos& point1, const PolarPos& point2);

	public:

		/// <summary>
		/// ����p�x�ƂȂ钼����̓��a
		/// </summary>
		/// <param name="a"> �p�x </param>
		/// <returns> ���a </returns>
		Optional<double> r(double a) const;

	};
}