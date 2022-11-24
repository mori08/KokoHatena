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

	private:

		// ACos(a)+BSin(a) = C/r

		// ���� Ax+By=C
		const double A;

		// ���� Ax+By=C
		const double B;

		// ���� Ax+By=C
		const double C;

	public:

		/// <param name="point1"> �n�_ </param>
		/// <param name="point2"> �I�_ </param>
		PolarLine(const PolarPos& point1, const PolarPos& point2);

	public:

		/// <summary>
		/// ��������w��̊p�x�ƂȂ钼����̓��a
		/// </summary>
		/// <param name="a"> �p�x </param>
		/// <returns> ���a , �w��̊p�x�ƂȂ�_���Ȃ��ꍇ none </returns>
		Optional<double> r(double a) const;

		/// <summary>
		/// ��������w��̋����ƂȂ钼����̕Ίp
		/// </summary>
		/// <param name="r"> ���� </param>
		/// <returns> �Ίp , 0 ~ 2�� </returns>
		std::list<double> a(double r) const;

		/// <summary>
		/// ���ar�̉~�Ƌ��L����������
		/// </summary>
		/// <param name="r"> ���a </param>
		/// <returns> true �̏ꍇ���L������ </returns>
		bool on(double r) const;

	};
}