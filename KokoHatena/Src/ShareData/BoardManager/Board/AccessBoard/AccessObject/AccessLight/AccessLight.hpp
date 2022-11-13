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

		std::list<Line> m_edgeList;

	public:

		AccessLight();

	public:

		/// <summary>
		/// �_������
		/// </summary>
		/// <returns> *this </returns>
		AccessLight& on()
		{
			m_on = true;
			return *this;
		}

		/// <summary>
		/// ��������
		/// </summary>
		/// <returns> *this </returns>
		AccessLight& off()
		{
			m_on = false;
			return *this;
		}

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
		/// <param name="rate"> �J�ڂ̊��� </param>
		/// <returns> *this </returns>
		AccessLight& setDirectionAngle(double directionAngle, double rate = 0);

		/// <summary>
		/// ���S�p�̐ݒ�
		/// </summary>
		/// <param name="centralAngle"> �����^�Ƃ����Ƃ��̒��S�p [0, 2Pi] </param>
		/// <param name="rate"> �J�ڂ̊��� </param>
		/// <returns> *this </returns>
		AccessLight& setCentralAngle(double centralAngle, double rate = 0);

		/// <summary>
		/// �����̐ݒ�
		/// </summary>
		/// <param name="distance"> �����ƌ����͂��ł������_�̋��� </param>
		/// <param name="rate"> �����̑J�� </param>
		/// <returns> *this </returns>
		AccessLight& setDistance(double distance, double rate = 0);

		/// <summary>
		/// ���̖��邳�̐ݒ�
		/// </summary>
		/// <param name="alpha"> ���̖��邳 MyWhite�̕s�����x [0, 1] </param>
		/// <returns> *this </returns>
		AccessLight& setAlpha(double alpha, double rate = 0);

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