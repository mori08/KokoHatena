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

		searchEdge();
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
				makeStraightPath(tl, br);
			}

			// �E�������̃`�F�b�N
			for (Point bl = tl + Point::Down(); isWalkAble(bl); bl.y++)
			{
				for (Point br = bl; isWalkAble(br); br.x++)
				{
					const int32 up = toInteger(br + Point::Up());
					if (m_path[i][up] != up) { break; }

					makeStraightPath(tl, br);
					makeStraightPath(Point(tl.x, br.y), Point(br.x, tl.y));

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

	void Terrain::makeStraightPath(const Point& s1, const Point& s2)
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

	void Terrain::searchEdge()
	{
		// ��Q��������̕ӂ̎Z�o
		for (int32 y : Range(0, HEIGHT))
		{
			Optional<std::pair<Point, Point>> line = none;

			for (int32 x : Range(0, WIDTH - 1))
			{
				if (!isWalkAble(Point(x, y)) && isWalkAble(Point(x, y - 1)))
				{
					// �ӂ��������Ƃ��͒[�_�̐ݒ�

					if (!line)
					{
						line = std::pair<Point, Point>();
						line->second = SQUARE_SIZE * Point(x, y);
					}
					line->first = SQUARE_SIZE * Point(x + 1, y);
				}
				else if(line)
				{
					// �ӂ��Ȃ������Ƃ��͕ӂ̒ǉ�
					m_edgeList.emplace_back(line.value());
					line = none;
				}
			}

			if (line)
			{
				m_edgeList.emplace_back(line.value());
			}
		}

		// ��Q���������̕ӂ̎Z�o
		for (int32 x : Range(0, WIDTH))
		{
			Optional<std::pair<Point, Point>> line = none;

			for (int32 y : Range(0, HEIGHT - 1))
			{
				if (!isWalkAble(Point(x, y)) && isWalkAble(Point(x - 1, y)))
				{
					// �ӂ��������Ƃ��͒[�_�̐ݒ�

					if (!line)
					{
						line = std::pair<Point, Point>();
						line->first = SQUARE_SIZE * Point(x, y);
					}
					line->second = SQUARE_SIZE * Point(x, y + 1);
				}
				else if (line)
				{
					// �ӂ��Ȃ������Ƃ��͕ӂ̒ǉ�
					m_edgeList.emplace_back(line.value());
					line = none;
				}
			}

			if (line)
			{
				m_edgeList.emplace_back(line.value());
			}
		}

		// ��Q���������̕ӂ̎Z�o
		for (int32 y : Range(-1, HEIGHT-1))
		{
			Optional<std::pair<Point, Point>> line = none;

			for (int32 x : Range(0, WIDTH - 1))
			{
				if (!isWalkAble(Point(x, y)) && isWalkAble(Point(x, y + 1)))
				{
					// �ӂ��������Ƃ��͒[�_�̐ݒ�

					if (!line)
					{
						line = std::pair<Point, Point>();
						line->first = SQUARE_SIZE * Point(x, y + 1);
					}
					line->second = SQUARE_SIZE * Point(x + 1, y + 1);
				}
				else if (line)
				{
					// �ӂ��Ȃ������Ƃ��͕ӂ̒ǉ�
					m_edgeList.emplace_back(line.value());
					line = none;
				}
			}

			if (line)
			{
				m_edgeList.emplace_back(line.value());
			}
		}

		// ��Q���E�����̕ӂ̎Z�o
		for (int32 x : Range(-1, WIDTH-1))
		{
			Optional<std::pair<Point, Point>> line = none;

			for (int32 y : Range(0, HEIGHT - 1))
			{
				if (!isWalkAble(Point(x, y)) && isWalkAble(Point(x + 1, y)))
				{
					// �ӂ��������Ƃ��͒[�_�̐ݒ�

					if (!line)
					{
						line = std::pair<Point, Point>();
						line->second = SQUARE_SIZE * Point(x + 1, y);
					}
					line->first = SQUARE_SIZE * Point(x + 1, y + 1);
				}
				else if (line)
				{
					// �ӂ��Ȃ������Ƃ��͕ӂ̒ǉ�
					m_edgeList.emplace_back(line.value());
					line = none;
				}
			}

			if (line)
			{
				m_edgeList.emplace_back(line.value());
			}
		}
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
				.draw(isWalkAble(i) ? ColorF(MyWhite, 0.5) : MyBlack)
				.drawFrame(2, MyBlack);
		}

#endif // _DEBUG
	}
}