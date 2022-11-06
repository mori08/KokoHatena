#include "Terrain.hpp"
#include "../../../../../MyLibrary/MyLibrary.hpp"
#include "../../../../../Config/Config.hpp"

namespace Kokoha
{
	Terrain::Terrain(const FilePath& filePath)
		: m_cellList(N, Cell::NONE)
	{
		loadCSV(filePath);

		searchPath();
	}

	void Terrain::loadCSV(const FilePath& filePath)
	{
		CSVData csv(filePath);

		for (int32 i : Range(0, N - 1))
		{
			const Point square = toSquare(i);
			const String cell = csv[square.y][square.x];

			// csvの内容に応じて地形データを書き換え
			if      (cell == U"o") { m_cellList[i] = Cell::BLOCK;    }
			else if (cell == U"x") { m_cellList[i] = Cell::SKELETON; }
		}
	}

	void Terrain::searchPath()
	{
		// 障害物のないマスのリストの作成
		std::list<int32> walkAbleList;
		for (int32 i : Range(0, N - 1))
		{
			if (isWalkAble(i)) { walkAbleList.push_back(i); }
		}

		// 辺の作成
		int32 max_area = 0;
		m_path = Array<Array<int32>>(N);
		for (int32 i : Range(0, N - 1)) { m_path[i] = Array<int32>(N, i); }
		m_dist = Array<Array<double>>(N, Array<double>(N, Inf<double>));
		for (int32 i : walkAbleList)
		{
			// 左上の座標
			Point tl = toSquare(i);

			// 右方向のチェック
			for (Point br = tl; isWalkAble(br); br.x++)
			{
				makeEdge(tl, br);
			}

			// 右下方向のチェック
			for (Point bl = tl + Point::Down(); isWalkAble(bl); bl.y++)
			{
				for (Point br = bl; isWalkAble(br); br.x++)
				{
					const int32 up = toInteger(br + Point::Up());
					if (m_path[i][up] != up) { break; }

					makeEdge(tl, br);
					makeEdge(Point(tl.x, br.y), Point(br.x, tl.y));

					// 最大面積の更新
					const int32 area = (br.x - tl.x + 1) * (br.y - tl.y + 1);
					if (max_area < area) { max_area = area; }
				}
			}
		}

		// 経路探索が必要なパス
		Array<std::list<int32>> needPathList(N);
		for (int32 i : walkAbleList)
		{
			for (int32 j : walkAbleList)
			{
				if (m_path[i][j] != j) { needPathList[i].push_back(j); }
			}
		}

		// 角の算出
		static const int32 WIDE_AREA = Config::get<int32>(U"AccessBoard.wideArea");
		static const Array<Point> CORNER_DIRECTION = { Point(+1,+1), Point(+1,-1), Point(-1,-1), Point(-1,+1) };
		std::list<int32> cornerList;
		for (int32 i : walkAbleList)
		{
			Point square = toSquare(i);

			for (const Point& d : CORNER_DIRECTION)
			{
				if (!isWalkAble(square + d) && isWalkAble(square + Point(d.x, 0)) && isWalkAble(square + Point(0, d.y)))
				{
					// 角になっているならリストに追加
					cornerList.emplace_back(i);
					break;
				}
			}
		}

		// ワーシャルフロイド
		for (int32 k : (max_area < WIDE_AREA) ? cornerList : walkAbleList)
		{
			for (int32 i : walkAbleList)
			{
				for (int32 j : needPathList[i])
				{
					if (m_dist[i][j] > m_dist[i][k] + m_dist[k][j])
					{
						m_dist[i][j] = m_dist[i][k] + m_dist[k][j];
						m_path[i][j] = m_path[i][k];
					}
				}
			}
		}
	}

	void Terrain::makeEdge(const Point& s1, const Point& s2)
	{
		const int32 i1 = toInteger(s1);
		const int32 i2 = toInteger(s2);

		// 経路の設定
		m_path[i1][i2] = i2;
		m_path[i2][i1] = i1;

		// 距離の設定
		const double distance = s1.distanceFrom(s2);
		m_dist[i1][i2] = distance;
		m_dist[i2][i1] = distance;
	}

	Vec2 Terrain::getPath(const Vec2& pixelS, const Vec2& pixelT) const
	{
		if (!isWalkAble(pixelS) || !isWalkAble(pixelT) || (pixelS - pixelT).isZero())
		{
			return Vec2::Zero();
		}

		const int32 iS = toInteger(pixelS); // 始点
		const int32 iT = toInteger(pixelT); // 終点
		const int32 iR = m_path[iS][iT];    // 中継地点

		if (iR == iT) // 直接目的地へ向かえる場合
		{
			return (pixelT - pixelS).normalize();
		}

		const Vec2 relay
			= toPixel(iR)
			+ (toPixel(m_path[iR][iT]) - toPixel(iR)).normalize() * SQUARE_SIZE / 2;

		return (relay - pixelS).normalize();
	}

	void Terrain::draw() const
	{
		for (int32 i : Range(0, N - 1))
		{
			if (isWalkAble(i)) { continue; }
			const Point square = toSquare(i);
			Rect(SQUARE_SIZE * square, SQUARE_SIZE).draw(MyBlack);
		}

#ifdef _DEBUG // デバッグモード 画面が
		static bool debugMode = false;
		debugMode ^= KeyQ.down();
		if (!debugMode) { return; }
		for (int32 i : Range(0, N - 1))
		{
			const Point square = toSquare(i);
			Rect(SQUARE_SIZE * square, SQUARE_SIZE)
				.draw(isWalkAble(i) ? ColorF(MyWhite, 0.2) : MyBlack)
				.drawFrame(2, MyBlack);
		}
#endif // _DEBUG
	}
}