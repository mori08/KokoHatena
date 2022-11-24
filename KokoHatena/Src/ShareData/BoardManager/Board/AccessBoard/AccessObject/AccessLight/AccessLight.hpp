#pragma once

#include "../../Terrain/Terrain.hpp"
#include "PolarLine/PolarLine.hpp"

namespace Kokoha
{
	/// <summary>
	/// AccessObject�����L�����
	/// </summary>
	class AccessLight
	{
	private: // ���̏���

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

		// ����\�����p�`
		Polygon m_polygon;

	private: // ���쐬���Ɏg�p

		/// <summary>
		/// �p�x���Ƃ̍s������
		/// </summary>
		class AngleEvent
		{
		public:
			double angle; // �p�x
			std::function<void()> func; // ����
			AngleEvent(double a, std::function<void()> f) : angle(a), func(f) {}
			bool operator<(const AngleEvent& another) const { return angle > another.angle; }
		};

		// ���_�z��
		Array<Vec2> m_posAry;

		// �Ӕz��
		Array<PolarLine> m_edgeAry;

		// �ӂ̃q�[�v �ł������ɋ߂��ӂ��擾�ł���
		Array<size_t> m_heap;

		// �Ӕԍ� -> �ؔԍ�
		Array<size_t> m_edgeToHeap;

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

	private:

		/// <summary>
		/// ������m_distance�̍��W��ǉ�
		/// </summary>
		/// <param name="angle"> �p�x </param>
		void addPoint(double angle);

		/// <summary>
		/// �ӂ̎n�_�̒ǉ�
		/// </summary>
		/// <param name="edgeId"> �Ӕԍ� </param>
		void addStartPoint(size_t edgeId);

		/// <summary>
		/// �ӂ̏I�_�̒ǉ�
		/// </summary>
		/// <param name="edgeId"> �Ӕԍ� </param>
		void addEndPoint(size_t edgeId);

		/// <summary>
		/// �q�[�v�擪�̕ӂ��擾
		/// </summary>
		/// <param name="angle"> �p�x </param>
		/// <returns> �q�[�v�擪�̕ӂ̊p�x�ɑΉ�����_�̓��a </returns>
		double heapTopR(double angle) const;

		/// <summary>
		/// �q�[�v�ɕӂ�ǉ�
		/// </summary>
		/// <param name="edgeId"> �Ӕԍ� </param>
		/// <param name="angle"> �p�x </param>
		void addEdgeToHeap(size_t edgeId, double angle);

		/// <summary>
		/// �q�[�v����ӂ��폜
		/// </summary>
		/// <param name="edgeId"> �Ӕԍ� </param>
		/// <param name="angle"> �p�x </param>
		void removeEdgeToHeap(size_t edgeId, double angle);

		/// <summary>
		/// ���_���t�]���Ȃ��Ȃ�܂ŏ�֏グ��
		/// </summary>
		/// <param name="i"> �ؔԍ� </param>
		/// <param name="angle"> �p�x </param>
		void heapUp(size_t i, double angle);

		/// <summary>
		/// ���_���t�]���Ȃ��Ȃ�܂ŉ��։�����
		/// </summary>
		/// <param name="i"> �ؔԍ� </param>
		/// <param name="angle"> �p�x </param>
		void heapDown(size_t i, double angle);

		/// <summary>
		/// �ӂ̔�r
		/// </summary>
		/// <param name="id1"> �ؔԍ�1 </param>
		/// <param name="id2"> �ؔԍ�2 </param>
		/// <param name="angle"> �p�x </param>
		/// <returns> ��1����2����O�ɂ���ꍇ true , �����łȂ��Ƃ� false </returns>
		bool compareEdge(size_t edgeId1, size_t edgeId2, double angle) const;

	};
}