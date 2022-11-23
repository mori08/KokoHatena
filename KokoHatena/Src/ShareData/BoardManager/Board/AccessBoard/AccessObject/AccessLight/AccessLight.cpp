#include "AccessLight.hpp"
#include <queue>
#include "../../../../../../MyLibrary/MyLibrary.hpp"

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

		// 辺リストの作成
		m_edgeAry.clear();
		for (const std::pair<Point, Point>& edge : terrain.getEdge())
		{
			if (twoVecToAngle(edge.first - m_sourcePos, edge.second - edge.first) > 0)
			{
				m_edgeAry.emplace_back
				(
					PolarPos(edge.first, m_sourcePos, m_directionAngle),
					PolarPos(edge.second, m_sourcePos, m_directionAngle)
				);
			}
		}

		// ヒープの初期化
		m_heap.clear();
		m_edgeToHeap = Array<size_t>(m_edgeAry.size());

		// イベントキューの作成
		std::priority_queue<AngleEvent> eventQueue;
		for (size_t edgeId = 0; edgeId < m_edgeAry.size(); ++edgeId)
		{
			if (m_edgeAry[edgeId].p2.a < m_edgeAry[edgeId].p1.a)
			{
				addEdgeToHeap(edgeId, -Math::Pi);
			}
			eventQueue.emplace(m_edgeAry[edgeId].p1.a, edgeId, true);
			eventQueue.emplace(m_edgeAry[edgeId].p2.a, edgeId, false);
		}

		// 頂点リストの作成
		Array<Vec2> posAry;
		while (!eventQueue.empty())
		{
			AngleEvent e = eventQueue.top();

			if (e.endP) // 始点の場合
			{
				// 頂点の追加
				const double minR = heapTopR(e.angle);
				if (Abs(m_edgeAry[e.edgeId].p1.r - minR) < 1e-5)
				{
					posAry << m_edgeAry[e.edgeId].p1.toOrthoPos(m_sourcePos, m_directionAngle);
				}
				else if (m_edgeAry[e.edgeId].p1.r < minR)
				{
					posAry << PolarPos(e.angle, heapTopR(e.angle)).toOrthoPos(m_sourcePos, m_directionAngle);
					posAry << m_edgeAry[e.edgeId].p1.toOrthoPos(m_sourcePos, m_directionAngle);
				}

				// 辺をヒープに追加
				addEdgeToHeap(e.edgeId, e.angle);
			}
			else // 終点の場合
			{
				// 辺をヒープから削除
				removeEdgeToHeap(e.edgeId, e.angle);

				// 頂点の追加
				const double minR = heapTopR(e.angle);
				if (Abs(m_edgeAry[e.edgeId].p2.r - minR) < 1e-5)
				{
					posAry << m_edgeAry[e.edgeId].p2.toOrthoPos(m_sourcePos, m_directionAngle);
				}
				else if (m_edgeAry[e.edgeId].p2.r < minR)
				{
					posAry << m_edgeAry[e.edgeId].p2.toOrthoPos(m_sourcePos, m_directionAngle);
					posAry << PolarPos(e.angle, heapTopR(e.angle)).toOrthoPos(m_sourcePos, m_directionAngle);
				}
			}

			eventQueue.pop();
		}

		m_polygon = Polygon(posAry);
	}

	void AccessLight::draw() const
	{
		if (!m_on) { return; }

		double direction = m_directionAngle - m_centralAngle / 2 + Math::HalfPi;

		while (direction < 0)
		{
			direction += Math::TwoPi;
		}
		while (direction > Math::TwoPi)
		{
			direction -= Math::TwoPi;
		}

		Circle(m_sourcePos, m_distance)
			.drawPie(
				direction, 
				m_centralAngle, ColorF(MyWhite, m_alpha)
			);

		m_polygon.draw(ColorF(MyWhite, m_alpha));
	}

	double AccessLight::heapTopR(double angle) const
	{
		return m_edgeAry[m_heap.front()].r(angle).value();
	}

	void AccessLight::addEdgeToHeap(size_t edgeId, double angle)
	{
		size_t i = m_edgeToHeap[edgeId] = m_heap.size();
		m_heap << edgeId;

		heapUp(i, angle);
	}

	void AccessLight::removeEdgeToHeap(size_t edgeId, double angle)
	{
		const size_t back = m_heap.back();   // ヒープ末尾の辺番号
		const size_t i = m_edgeToHeap[edgeId]; // 削除する箇所

		// 末尾の辺を削除する箇所へ上書き
		m_heap[i] = back;
		m_edgeToHeap[back] = i;

		// ヒープ末尾を削除
		m_heap.pop_back();

		if (i == m_heap.size()) { return; }

		heapUp(i, angle);
		heapDown(i, angle);
	}

	void AccessLight::heapUp(size_t i, double angle)
	{
		const size_t edgeId = m_heap[i];

		// 頂点が逆転しなくなるまで上げる
		while (i > 0)
		{
			const size_t p = (i - 1) / 2; // 親の木番号

			// 親の方が近いとき終了
			if (compareEdge(p, i, angle)) { break; }

			// 親を一つ下げる
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

		// 頂点が逆転しなくなるまで下げる
		while (i * 2 + 1 < m_heap.size())
		{
			// 子同士を比較
			size_t x = i * 2 + 1, y = i * 2 + 2;
			if (y < m_heap.size() && compareEdge(y, x, angle)) { x = y; }

			// 子の方が遠いとき終了
			if (compareEdge(i, x, angle)) { break; }

			// 子を一つ上げる
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