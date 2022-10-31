#pragma once

#include <Siv3D.hpp>

/*
	3種類の座標を以下の表現で使い分ける.
	int32 integer -> 整数値       : データの管理で使用
	Vec2  pixel   -> ピクセル座標 : 当たり判定や描画に使用
	Point square  -> マス座標     : 障害物の管理や経路探索に使用
*/

namespace Kokoha
{
	/// <summary>
	/// 地形データ
	/// オブジェクトの移動と光の描画で使用 
	/// </summary>
	class StageData
	{
	public:

		// 各マスの状態
		enum class Cell
		{
			NONE,     // 光 -> 通す , オブジェクト -> 通す
			SKELETON, // 光 -> 通す , オブジェクト -> 通さない
			BLOCK     // 光 -> 通さない , オブジェクト -> 通さない
		};

	private:

		static constexpr int32 WIDTH       = 24;           // ステージの幅(マス)
		static constexpr int32 HEIGHT      = 18;           // ステージの高さ(マス)
		static constexpr int32 SIZE        = WIDTH*HEIGHT; // マス数
		static constexpr int32 SQUARE_SIZE = 25;           // 1マスの1辺の長さ(ピクセル)

	private:

		// 地形データ
		Array<Cell> m_terrain;

	private:

		/// <summary>
		/// マス座標を整数値に変換
		/// </summary>
		/// <param name="square"> マス座標 </param>
		/// <returns> マス座標に対する整数値 </returns>
		static constexpr int32 toInteger(const Point& square)
		{
			return square.x + WIDTH * square.y;
		}

		/// <summary>
		/// ピクセル座標を整数値に変換
		/// </summary>
		/// <param name="pixel"> ピクセル座標 </param>
		/// <returns> ピクセル座標があるマス座標に対応する整数値 </returns>
		static constexpr int32 toInteger(const Vec2& pixel)
		{
			return toInteger(toSquare(pixel));
		}

		/// <summary>
		/// 整数値をマス座標に変換
		/// </summary>
		/// <param name="integer"> 整数値 </param>
		/// <returns> 整数値に対応するマス座標 </returns>
		static constexpr Point toSquare(int32 integer)
		{
			return Point(integer % WIDTH, integer / WIDTH);
		}

		/// <summary>
		/// ピクセル座標をマス座標に変換
		/// </summary>
		/// <param name="pixel"> ピクセル座標 </param>
		/// <returns> ピクセル座標があるマスのマス座標 </returns>
		static constexpr Point toSquare(const Vec2& pixel)
		{
			return Floor(pixel / SQUARE_SIZE).asPoint();
		}

		/// <summary>
		/// 整数値をピクセル座標に変換
		/// </summary>
		/// <param name="integer"> 整数値 </param>
		/// <returns> 整数値に対応するマス座標の中心ピクセル座標 </returns>
		static constexpr Vec2 toPixel(int32 integer)
		{
			return toPixel(toSquare(integer));
		}

		/// <summary>
		/// マス座標をピクセル座標に変換
		/// </summary>
		/// <param name="square"> マス座標 </param>
		/// <returns> マスの中心のピクセル座標 </returns>
		static constexpr Vec2 toPixel(const Point& square)
		{
			return SQUARE_SIZE * (Vec2::One() * square + Vec2::One() / 2);
		}

	};
}