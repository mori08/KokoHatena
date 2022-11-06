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

			// csv�̓��e�ɉ����Ēn�`�f�[�^����������
			if      (cell == U"o") { m_cellList[i] = Cell::BLOCK;    }
			else if (cell == U"x") { m_cellList[i] = Cell::SKELETON; }
		}
	}

	void Terrain::searchPath()
	{
		// ��Q���̂Ȃ��}�X�̃��X�g�̍쐬
		std::list<int32> walkAbleList;
		for (int32 i : Range(0, N - 1))
		{
			if (isWalkAble(i)) { walkAbleList.push_back(i); }
		}

		// �ӂ̍쐬
		int32 max_area = 0;
		m_path = Array<Array<int32>>(N);
		for (int32 i : Range(0, N - 1)) { m_path[i] = Array<int32>(N, i); }
		m_dist = Array<Array<double>>(N, Array<double>(N, Inf<double>));
		for (int32 i : walkAbleList)
		{
			// ����̍��W
			Point tl = toSquare(i);

			// �E�����̃`�F�b�N
			for (Point br = tl; isWalkAble(br); br.x++)
			{
				makeEdge(tl, br);
			}

			// �E�������̃`�F�b�N
			for (Point bl = tl + Point::Down(); isWalkAble(bl); bl.y++)
			{
				for (Point br = bl; isWalkAble(br); br.x++)
				{
					const int32 up = toInteger(br + Point::Up());
					if (m_path[i][up] != up) { break; }

					makeEdge(tl, br);
					makeEdge(Point(tl.x, br.y), Point(br.x, tl.y));

					// �ő�ʐς̍X�V
					const int32 area = (br.x - tl.x + 1) * (br.y - tl.y + 1);
					if (max_area < area) { max_area = area; }
				}
			}
		}

		// �o�H�T�����K�v�ȃp�X
		Array<std::list<int32>> needPathList(N);
		for (int32 i : walkAbleList)
		{
			for (int32 j : walkAbleList)
			{
				if (m_path[i][j] != j) { needPathList[i].push_back(j); }
			}
		}

		// �p�̎Z�o
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
					// �p�ɂȂ��Ă���Ȃ烊�X�g�ɒǉ�
					cornerList.emplace_back(i);
					break;
				}
			}
		}

		// ���[�V�����t���C�h
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

		// �o�H�̐ݒ�
		m_path[i1][i2] = i2;
		m_path[i2][i1] = i1;

		// �����̐ݒ�
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

		const int32 iS = toInteger(pixelS); // �n�_
		const int32 iT = toInteger(pixelT); // �I�_
		const int32 iR = m_path[iS][iT];    // ���p�n�_

		if (iR == iT) // ���ږړI�n�֌�������ꍇ
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

#ifdef _DEBUG // �f�o�b�O���[�h ��ʂ�
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