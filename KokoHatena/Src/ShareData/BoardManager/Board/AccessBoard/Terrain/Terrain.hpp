#pragma once

#include <Siv3D.hpp>

/*
	3��ނ̍��W���ȉ��̕\���Ŏg��������.
	int32 integer -> �����l       : �f�[�^�̊Ǘ��Ŏg�p
	Vec2  pixel   -> �s�N�Z�����W : �����蔻���`��Ɏg�p
	Point square  -> �}�X���W     : ��Q���̊Ǘ���o�H�T���Ɏg�p
*/

namespace Kokoha
{
	/// <summary>
	/// �n�`�f�[�^
	/// �I�u�W�F�N�g�̈ړ��ƌ��̕`��Ŏg�p 
	/// </summary>
	class Terrain
	{
	public:

		// �e�}�X�̏��
		enum class Cell
		{
			NONE,     // �� -> �ʂ� , �I�u�W�F�N�g -> �ʂ�
			SKELETON, // �� -> �ʂ� , �I�u�W�F�N�g -> �ʂ��Ȃ�
			BLOCK     // �� -> �ʂ��Ȃ� , �I�u�W�F�N�g -> �ʂ��Ȃ�
		};

	private:

		static constexpr int32 WIDTH       = 24;           // �X�e�[�W�̕�(�}�X)
		static constexpr int32 HEIGHT      = 18;           // �X�e�[�W�̍���(�}�X)
		static constexpr int32 N           = WIDTH*HEIGHT; // �}�X��
		static constexpr int32 SQUARE_SIZE = 25;           // 1�}�X��1�ӂ̒���(�s�N�Z��)

	private:

		// �n�`�f�[�^
		Array<Cell> m_cellList;

		// [i][j] : i -> j �ւ̍ŒZ�o�H�i���̖ڕW�j
		Array<Array<int32>> m_path;

		// [i][j] : i -> j �ւ̍ŒZ�o�H�i1�}�X��1�ӂ�1�Ƃ��������j
		Array<Array<double>> m_dist;

	private:

		/// <summary>
		/// �}�X���W�𐮐��l�ɕϊ�
		/// </summary>
		/// <param name="square"> �}�X���W </param>
		/// <returns> �}�X���W�ɑ΂��鐮���l </returns>
		static constexpr int32 toInteger(const Point& square)
		{
			return square.x + WIDTH * square.y;
		}

		/// <summary>
		/// �s�N�Z�����W�𐮐��l�ɕϊ�
		/// </summary>
		/// <param name="pixel"> �s�N�Z�����W </param>
		/// <returns> �s�N�Z�����W������}�X���W�ɑΉ����鐮���l </returns>
		static constexpr int32 toInteger(const Vec2& pixel)
		{
			return toInteger(toSquare(pixel));
		}

		/// <summary>
		/// �����l���}�X���W�ɕϊ�
		/// </summary>
		/// <param name="integer"> �����l </param>
		/// <returns> �����l�ɑΉ�����}�X���W </returns>
		static constexpr Point toSquare(int32 integer)
		{
			return Point(integer % WIDTH, integer / WIDTH);
		}

		/// <summary>
		/// �s�N�Z�����W���}�X���W�ɕϊ�
		/// </summary>
		/// <param name="pixel"> �s�N�Z�����W </param>
		/// <returns> �s�N�Z�����W������}�X�̃}�X���W </returns>
		static constexpr Point toSquare(const Vec2& pixel)
		{
			return Floor(pixel / SQUARE_SIZE).asPoint();
		}

		/// <summary>
		/// �����l���s�N�Z�����W�ɕϊ�
		/// </summary>
		/// <param name="integer"> �����l </param>
		/// <returns> �����l�ɑΉ�����}�X���W�̒��S�s�N�Z�����W </returns>
		static constexpr Vec2 toPixel(int32 integer)
		{
			return toPixel(toSquare(integer));
		}

		/// <summary>
		/// �}�X���W���s�N�Z�����W�ɕϊ�
		/// </summary>
		/// <param name="square"> �}�X���W </param>
		/// <returns> �}�X�̒��S�̃s�N�Z�����W </returns>
		static constexpr Vec2 toPixel(const Point& square)
		{
			return SQUARE_SIZE * (Vec2::One() * square + Vec2::One() / 2);
		}

	public:

		/// <param name="filePath"> �n�`�f�[�^��CSV�t�@�C���ւ̃p�X </param>
		Terrain(const FilePath& filePath);

	private:

		/// <summary>
		/// csv�t�@�C���̓ǂݍ��݂ƒn�`�̐ݒ�
		/// </summary>
		void loadCSV(const FilePath& filePath);

		/// <summary>
		/// �o�H�T��
		/// </summary>
		void searchPath();

		/// <summary>
		/// �}�X1�ƃ}�X2�̊Ԃɒ����̌o�H��ݒ�
		/// </summary>
		/// <param name="s1"> �}�X1 </param>
		/// <param name="s2"> �}�X2 </param>
		void makeEdge(const Point& s1, const Point& s2);

	public:

		/// <summary>
		/// �w�肳�ꂽ�}�X���ʍs�\��
		/// </summary>
		/// <param name="square"> �}�X���W </param>
		/// <returns> true �̂Ƃ��ʍs�\ , false �̂Ƃ��ʍs�s�� </returns>
		bool isWalkAble(const Point& square) const
		{
			return true
				&& square.x >= 0
				&& square.x < WIDTH
				&& square.y >= 0
				&& square.y < HEIGHT
				&& m_cellList[toInteger(square)] == Cell::NONE;
		}

		/// <summary>
		/// �w�肳�ꂽ�����l�ɑΉ�����}�X���ʍs�\��
		/// </summary>
		/// <param name="integer"> �����l </param>
		/// <returns> true �̂Ƃ��ʍs�\ , false �̂Ƃ��ʍs�s�� </returns>
		bool isWalkAble(int32 integer) const
		{
			return isWalkAble(toSquare(integer));
		}

		/// <summary>
		/// �w�肳�ꂽ�s�N�Z�����W���ʍs�\��
		/// </summary>
		/// <param name="pixel"> �s�N�Z�����W </param>
		/// <returns> true �̂Ƃ��ʍs�\ , false �̂Ƃ��ʍs�s�� </returns>
		bool isWalkAble(const Vec2& pixel) const
		{
			return isWalkAble(toSquare(pixel));
		}

		/// <summary>
		/// �ŒZ�o�H�̎擾
		/// </summary>
		/// <param name="pixelS"> �n�_�i�s�N�Z�����W�j </param>
		/// <param name="pixelT"> �I�_�i�s�N�Z�����W�j </param>
		/// <returns> �o�H��ōŏ��ɐi�ޕ����̒P�ʃx�N�g�� or Vec2::Zero() </returns>
		Vec2 getPath(const Vec2& pixelS, const Vec2& pixelT) const;

		/// <summary>
		/// �`��
		/// </summary>
		void draw() const;
	};
}