#pragma once

#include "../../Terrain/Terrain.hpp"

namespace Kokoha
{
	/// <summary>
	/// AccessObject�����L�����
	/// </summary>
	class AccessLight
	{
	private:

		// true �Ȃ� �_�� , false �Ȃ� ����
		bool m_on;

		// �����ƂȂ钆�S���W
		Vec2 m_sourcePos;

		// �����˂����� [0,2Pi]
		double m_directionAngle;

		// ���S�p [0,2Pi]
		double m_centralAngle;

		// ��������̌����͂����� [0, 2Pi] 
		double m_distance;

		// ���̖��邳 [0, 1]
		double m_alpha;

	public:

		AccessLight();

	public:

		/// <summary>
		/// �����̍��W�̐ݒ�
		/// </summary>
		/// <param name="sourcePos"> �����̍��W </param>
		/// <returns> *this </returns>
		AccessLight& setSourcePos(const Vec2& sourcePos)
		{
			m_sourcePos = sourcePos;
			return *this;
		}

		/// <summary>
		/// �������������̐ݒ�
		/// </summary>
		/// <param name="directionAngle"> �������������ix��+�̕�����0�Ƃ����Ƃ��̍����̊p�x [0, 2Pi]�j </param>
		/// <returns> *this </returns>
		AccessLight& setDirectionAngle(double directionAngle)
		{
			m_directionAngle = Clamp(directionAngle, 0.0, Math::TwoPi);
			return *this;
		}

		/// <summary>
		/// ���S�p�̐ݒ�
		/// </summary>
		/// <param name="centralAngle"> �����^�Ƃ����Ƃ��̒��S�p [0, 2Pi] </param>
		/// <returns> *this </returns>
		AccessLight& setCentralAngle(double centralAngle)
		{
			m_centralAngle = Clamp(centralAngle, 0.0, Math::TwoPi);
			return *this;
		}

		/// <summary>
		/// �����̐ݒ�
		/// </summary>
		/// <param name="distance"> �����ƌ����͂��ł������_�̋��� </param>
		/// <returns> *this </returns>
		AccessLight& setDistance(double distance)
		{
			m_distance = Max(0.0, distance);
			return *this;
		}

		/// <summary>
		/// ���̖��邳�̐ݒ�
		/// </summary>
		/// <param name="alpha"> ���̖��邳 MyWhite�̕s�����x [0, 1] </param>
		/// <returns> *this </returns>
		AccessLight& setAlpha(double alpha)
		{
			m_alpha = alpha;
			return *this;
		}

		/// <summary>
		/// �X�V
		/// </summary>
		/// <param name="terrain"> �n�`�f�[�^ </param>
		void update(const Terrain& terrain);

		/// <summary>
		/// �`��
		/// </summary>
		void draw() const;

	};
}