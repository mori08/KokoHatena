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
	class StageData
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
		static constexpr int32 SIZE        = WIDTH*HEIGHT; // �}�X��
		static constexpr int32 SQUARE_SIZE = 25;           // 1�}�X��1�ӂ̒���(�s�N�Z��)

	private:

		// �n�`�f�[�^
		Array<Cell> m_terrain;

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

	};
}