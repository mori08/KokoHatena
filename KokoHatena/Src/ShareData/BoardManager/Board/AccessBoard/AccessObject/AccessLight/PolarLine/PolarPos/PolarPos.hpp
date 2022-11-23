#pragma once

#include <Siv3D.hpp>

namespace Kokoha
{
	/// <summary>
	/// �ɍ��W
	/// </summary>
	class PolarPos
	{
	public:

		// �Ίp in [-Pi,Pi]
		const double a;

		// ���a in [0, Inf)
		const double r;

	public:

		/// <summary>
		/// �Ίp�Ƌ�������ɍ��W���쐬
		/// </summary>
		/// <param name="angle"> �Ίp </param>
		/// <param name="distance"> ���� </param>
		PolarPos(double angle, double distance);

		PolarPos(const PolarPos& another);

		/// <summary>
		/// �������W����ϊ�
		/// </summary>
		/// <param name="pos"> �������W </param>
		/// <param name="originPos"> r=0�ƂȂ�_�̒������W </param>
		/// <param name="initalLineAngle"> �n���̊p�x </param>
		PolarPos(const Vec2& pos, const Vec2& originPos, double initalLineAngle);

		

		/// <summary>
		/// �������W�֕ϊ�
		/// </summary>
		/// <param name="originPos"> r=0�ƂȂ�_�̒������W </param>
		/// <param name="initialLineAngle"> �n���̊p�x </param>
		/// <returns> �������W </returns>
		Vec2 toOrthoPos(const Vec2& originPos, double initialLineAngle) const;

	};
}