#include "AccessLight.hpp"
#include <queue>
#include "../../../../../../MyLibrary/MyLibrary.hpp"
#include "../../../../../../Config/Config.hpp"

namespace
{
	constexpr double EPSILON = 1e-5;
}

namespace Kokoha
{
	AccessLight::AccessLight()
		: m_on(false)
		, m_sourcePos(Vec2::Zero())
		, m_directionAngle(0)
		, m_centralAngle(0)
		, m_distance(0)
		, m_alpha(0)
	{

	}

	AccessLight& AccessLight::setDirectionAngle(double directionAngle, double rate)
	{
		internalDividingPoint(m_directionAngle, directionAngle, rate);
		return *this;
	}

	AccessLight& AccessLight::setCentralAngle(double centralAngle, double rate)
	{
		internalDividingPoint(m_centralAngle, centralAngle, rate);
		return *this;
	}

	AccessLight& AccessLight::setDistance(double distance, double rate)
	{
		internalDividingPoint(m_distance, distance, rate);
		return *this;
	}

	AccessLight& AccessLight::setAlpha(double alpha, double rate)
	{
		internalDividingPoint(m_alpha, alpha, rate);
		return *this;
	}

	void AccessLight::update(const Terrain& terrain)
	{
		if (!m_on || m_centralAngle == 0 || m_distance == 0 || m_alpha == 0)
		{
			return;
		}

		if (!terrain.isWalkAble(m_sourcePos))
		{
			m_on = false;
			return;
		}

		m_isPie = m_centralAngle < Math::TwoPi - EPSILON;

		uint64 time = Time::GetMicrosec();
		if (Scene::FrameCount() % 60 == 0)
		{
			ClearPrint();
		}

		// �Ӄ��X�g�̍쐬
		m_edgeAry.clear();
		for (const std::pair<Point, Point>& edge : terrain.getEdge())
		{
			PolarLine polarLine
			(
				PolarPos(edge.first, m_sourcePos, m_directionAngle),
				PolarPos(edge.second, m_sourcePos, m_directionAngle)
			);

			if (polarLine.on(m_distance) && twoVecToAngle(edge.first - m_sourcePos, edge.second - edge.first) > 0)
			{
				m_edgeAry.emplace_back(polarLine);
			}
		}

		if (Scene::FrameCount() % 60 == 0)
		{
			Print << U"[�Ӄ��X�g�̍쐬]";
			Print << U"��������(s) : " << (Time::GetMicrosec() - time)*1e-6;
			Print << U"�ӂ̐� : " << terrain.getEdge().size();
			Print << U"�Ӄ��X�g�̃T�C�Y : " << m_edgeAry.size();
			time = Time::GetMicrosec();
		}

		// �q�[�v�̏�����
		m_heap.clear();
		m_edgeToHeap = Array<size_t>(m_edgeAry.size());

		// �ӂ̃C�x���g���쐬
		std::priority_queue<AngleEvent> eventQueue;
		for (size_t edgeId = 0; edgeId < m_edgeAry.size(); ++edgeId)
		{
			// �ӂ����O�ɒǉ�
			if (m_edgeAry[edgeId].p2.a < m_edgeAry[edgeId].p1.a)
			{
				addEdgeToHeap(edgeId, -Math::Pi);
			}

			// �ӂ̃C�x���g�̍쐬
			eventQueue.emplace(m_edgeAry[edgeId].p1.a, [this, edgeId]() { addStartPoint(edgeId); });
			eventQueue.emplace(m_edgeAry[edgeId].p2.a, [this, edgeId]() { addEndPoint(edgeId);   });
			for (const auto& angle : m_edgeAry[edgeId].a(m_distance))
			{
				eventQueue.emplace(angle, [this, angle]() { addPoint(angle);});
			}
		}

		if (Scene::FrameCount() % 60 == 0)
		{
			Print << U"�ӃC�x���g�̍쐬]";
			Print << U"��������(s) : " << (Time::GetMicrosec() - time)*1e-6;
			Print << U"�C�x���g�̐� : " << eventQueue.size();
			time = Time::GetMicrosec();
		}

		// �~�̃C�x���g�̍쐬
		const int32 QUALITY = Config::get<int32>(U"AccessLight.quality");
		for (int32 i = 0; i <= QUALITY; ++i)
		{
			const double angle = -Math::Pi + Math::TwoPi * i / QUALITY;
			eventQueue.emplace(angle, [this, angle]() { addPoint(angle); });
		}
		if (m_isPie)
		{
			eventQueue.emplace(-m_centralAngle/2, [this]() { addPiePoint(-m_centralAngle/2); });
			eventQueue.emplace(+m_centralAngle/2, [this]() { addPiePoint(+m_centralAngle/2); });
		}

		if (Scene::FrameCount() % 60 == 0)
		{
			Print << U"[�~�C�x���g�̍쐬]";
			Print << U"��������(s) : " << (Time::GetMicrosec() - time)*1e-6;
			Print << U"�C�x���g�̐� : " << eventQueue.size();
			time = Time::GetMicrosec();
		}

		// ���_���X�g�̍쐬
		m_posAry.clear();
		if (m_isPie) { m_posAry.emplace_back(m_sourcePos); }
		while (!eventQueue.empty())
		{
			eventQueue.top().func();
			eventQueue.pop();
		}

		if (Scene::FrameCount() % 60 == 0)
		{
			Print << U"[���_���X�g�̍쐬]";
			Print << U"��������(s) : " << (Time::GetMicrosec() - time)*1e-6;
			Print << U"���_�̐� : " << m_posAry.size();
			time = Time::GetMicrosec();
		}

		m_polygon = Polygon(m_posAry);

		if (Scene::FrameCount() % 60 == 0)
		{
			Print << U"[�|���S���̍쐬]";
			Print << U"��������(s) : " << (Time::GetMicrosec() - time)*1e-6;
			time = Time::GetMicrosec();
		}
	}

	void AccessLight::draw() const
	{
		if (!m_on) { return; }

		uint64 time = Time::GetMicrosec();

		m_polygon.draw(ColorF(MyWhite, m_alpha));

		if (Scene::FrameCount() % 60 == 0)
		{
			Print << U"[���̕`��]";
			Print << U"��������(s) : " << (Time::GetMicrosec() - time)*1e-6;
			time = Time::GetMicrosec();
		}
	}

	void AccessLight::addPoint(double angle)
	{
		const double minR = heapTopR(angle);

		if (m_isPie && !clockwise(-m_centralAngle / 2, angle, m_centralAngle / 2))
		{
			return;
		}

		if (m_distance < minR + EPSILON)
		{
			m_posAry << PolarPos(angle, m_distance).toOrthoPos(m_sourcePos, m_directionAngle);
		}
	}

	void AccessLight::addPiePoint(double angle)
	{
		m_posAry << PolarPos(angle, Min(m_distance, heapTopR(angle))).toOrthoPos(m_sourcePos, m_directionAngle);
	}

	void AccessLight::addStartPoint(size_t edgeId)
	{
		const double a = m_edgeAry[edgeId].p1.a; // �n�_�̕Ίp
		const double r = m_edgeAry[edgeId].p1.r; // �n�_�̓��a

		const double minR = Min(heapTopR(a), m_distance); // �����͂�����

		if (m_isPie && !clockwise(-m_centralAngle / 2, a, m_centralAngle / 2))
		{
			// ��^�̊O���Ȃ璸�_�͒ǉ����Ȃ�
		}
		else if (Abs(r - minR) < EPSILON)
		{
			m_posAry << m_edgeAry[edgeId].p1.toOrthoPos(m_sourcePos, m_directionAngle);
		}
		else if (r < minR)
		{
			m_posAry << PolarPos(a, minR).toOrthoPos(m_sourcePos, m_directionAngle);
			m_posAry << m_edgeAry[edgeId].p1.toOrthoPos(m_sourcePos, m_directionAngle);
		}

		// �ӂ��q�[�v�ɒǉ�
		addEdgeToHeap(edgeId, a);
	}

	void AccessLight::addEndPoint(size_t edgeId)
	{
		const double a = m_edgeAry[edgeId].p2.a; // �I�_�̕Ίp
		const double r = m_edgeAry[edgeId].p2.r; // �I�_�̓��a

		// �ӂ��q�[�v����폜
		removeEdgeToHeap(edgeId, a);

		const double minR = Min(heapTopR(a), m_distance); // �����͂�����
		
		if (m_isPie && !clockwise(-m_centralAngle / 2, a, m_centralAngle / 2))
		{
			// ��^�̊O���Ȃ璸�_�͒ǉ����Ȃ�
		}
		else if (Abs(r - minR) < EPSILON)
		{
			m_posAry << m_edgeAry[edgeId].p2.toOrthoPos(m_sourcePos, m_directionAngle);
		}
		else if (r < minR)
		{
			m_posAry << m_edgeAry[edgeId].p2.toOrthoPos(m_sourcePos, m_directionAngle);
			m_posAry << PolarPos(a, minR).toOrthoPos(m_sourcePos, m_directionAngle);
		}
	}

	double AccessLight::heapTopR(double angle) const
	{
		return m_heap.empty()
			? m_distance
			: m_edgeAry[m_heap.front()].r(angle).value();
	}

	void AccessLight::addEdgeToHeap(size_t edgeId, double angle)
	{
		size_t i = m_edgeToHeap[edgeId] = m_heap.size();
		m_heap << edgeId;

		heapUp(i, angle);
	}

	void AccessLight::removeEdgeToHeap(size_t edgeId, double angle)
	{
		const size_t back = m_heap.back();   // �q�[�v�����̕Ӕԍ�
		const size_t i = m_edgeToHeap[edgeId]; // �폜����ӏ�

		// �����̕ӂ��폜����ӏ��֏㏑��
		m_heap[i] = back;
		m_edgeToHeap[back] = i;

		// �q�[�v�������폜
		m_heap.pop_back();

		if (i == m_heap.size()) { return; }

		heapUp(i, angle);
		heapDown(i, angle);
	}

	void AccessLight::heapUp(size_t i, double angle)
	{
		const size_t edgeId = m_heap[i];

		// ���_���t�]���Ȃ��Ȃ�܂ŏグ��
		while (i > 0)
		{
			const size_t p = (i - 1) / 2; // �e�̖ؔԍ�

			// �e�̕����߂��Ƃ��I��
			if (compareEdge(p, i, angle)) { break; }

			// �e���������
			m_heap[i] = m_heap[p];
			m_edgeToHeap[m_heap[i]] = i;

			i = p;
			m_heap[i] = edgeId;
			m_edgeToHeap[edgeId] = i;
		}

		m_heap[i] = edgeId;
		m_edgeToHeap[edgeId] = i;
	}

	void AccessLight::heapDown(size_t i, double angle)
	{
		const size_t edgeId = m_heap[i];

		// ���_���t�]���Ȃ��Ȃ�܂ŉ�����
		while (i * 2 + 1 < m_heap.size())
		{
			// �q���m���r
			size_t x = i * 2 + 1, y = i * 2 + 2;
			if (y < m_heap.size() && compareEdge(y, x, angle)) { x = y; }

			// �q�̕��������Ƃ��I��
			if (compareEdge(i, x, angle)) { break; }

			// �q����グ��
			m_heap[i] = m_heap[x];
			m_edgeToHeap[m_heap[i]] = i;

			i = x;
			m_heap[i] = edgeId;
			m_edgeToHeap[edgeId] = i;
		}

		m_heap[i] = edgeId;
		m_edgeToHeap[edgeId] = i;
	}

	bool AccessLight::compareEdge(size_t edgeId1, size_t edgeId2, double angle) const
	{
		return m_edgeAry[m_heap[edgeId1]].r(angle).value()
			< m_edgeAry[m_heap[edgeId2]].r(angle).value();
	}
}