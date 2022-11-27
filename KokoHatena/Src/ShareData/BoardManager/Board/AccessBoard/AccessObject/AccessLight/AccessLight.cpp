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

		// 辺リストの作成
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
			Print << U"[辺リストの作成]";
			Print << U"処理時間(s) : " << (Time::GetMicrosec() - time)*1e-6;
			Print << U"辺の数 : " << terrain.getEdge().size();
			Print << U"辺リストのサイズ : " << m_edgeAry.size();
			time = Time::GetMicrosec();
		}

		// ヒープの初期化
		m_heap.clear();
		m_edgeToHeap = Array<size_t>(m_edgeAry.size());

		// 辺のイベントを作成
		std::priority_queue<AngleEvent> eventQueue;
		for (size_t edgeId = 0; edgeId < m_edgeAry.size(); ++edgeId)
		{
			// 辺を事前に追加
			if (m_edgeAry[edgeId].p2.a < m_edgeAry[edgeId].p1.a)
			{
				addEdgeToHeap(edgeId, -Math::Pi);
			}

			// 辺のイベントの作成
			eventQueue.emplace(m_edgeAry[edgeId].p1.a, [this, edgeId]() { addStartPoint(edgeId); });
			eventQueue.emplace(m_edgeAry[edgeId].p2.a, [this, edgeId]() { addEndPoint(edgeId);   });
			for (const auto& angle : m_edgeAry[edgeId].a(m_distance))
			{
				eventQueue.emplace(angle, [this, angle]() { addPoint(angle);});
			}
		}

		if (Scene::FrameCount() % 60 == 0)
		{
			Print << U"辺イベントの作成]";
			Print << U"処理時間(s) : " << (Time::GetMicrosec() - time)*1e-6;
			Print << U"イベントの数 : " << eventQueue.size();
			time = Time::GetMicrosec();
		}

		// 円のイベントの作成
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
			Print << U"[円イベントの作成]";
			Print << U"処理時間(s) : " << (Time::GetMicrosec() - time)*1e-6;
			Print << U"イベントの数 : " << eventQueue.size();
			time = Time::GetMicrosec();
		}

		// 頂点リストの作成
		m_posAry.clear();
		if (m_isPie) { m_posAry.emplace_back(m_sourcePos); }
		while (!eventQueue.empty())
		{
			eventQueue.top().func();
			eventQueue.pop();
		}

		if (Scene::FrameCount() % 60 == 0)
		{
			Print << U"[頂点リストの作成]";
			Print << U"処理時間(s) : " << (Time::GetMicrosec() - time)*1e-6;
			Print << U"頂点の数 : " << m_posAry.size();
			time = Time::GetMicrosec();
		}

		m_polygon = Polygon(m_posAry);

		if (Scene::FrameCount() % 60 == 0)
		{
			Print << U"[ポリゴンの作成]";
			Print << U"処理時間(s) : " << (Time::GetMicrosec() - time)*1e-6;
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
			Print << U"[光の描画]";
			Print << U"処理時間(s) : " << (Time::GetMicrosec() - time)*1e-6;
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
		const double a = m_edgeAry[edgeId].p1.a; // 始点の偏角
		const double r = m_edgeAry[edgeId].p1.r; // 始点の動径

		const double minR = Min(heapTopR(a), m_distance); // 光が届く距離

		if (m_isPie && !clockwise(-m_centralAngle / 2, a, m_centralAngle / 2))
		{
			// 扇型の外側なら頂点は追加しない
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

		// 辺をヒープに追加
		addEdgeToHeap(edgeId, a);
	}

	void AccessLight::addEndPoint(size_t edgeId)
	{
		const double a = m_edgeAry[edgeId].p2.a; // 終点の偏角
		const double r = m_edgeAry[edgeId].p2.r; // 終点の動径

		// 辺をヒープから削除
		removeEdgeToHeap(edgeId, a);

		const double minR = Min(heapTopR(a), m_distance); // 光が届く距離
		
		if (m_isPie && !clockwise(-m_centralAngle / 2, a, m_centralAngle / 2))
		{
			// 扇型の外側なら頂点は追加しない
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