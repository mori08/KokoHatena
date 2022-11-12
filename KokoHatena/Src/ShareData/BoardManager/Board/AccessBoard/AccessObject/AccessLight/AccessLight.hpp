#pragma once

#include "../../Terrain/Terrain.hpp"

namespace Kokoha
{
	/// <summary>
	/// AccessObjectが所有する光
	/// </summary>
	class AccessLight
	{
	private:

		// true なら 点灯 , false なら 消灯
		bool m_on;

		// 光源となる中心座標
		Vec2 m_sourcePos;

		// 光が射す方向 [0,2Pi]
		double m_directionAngle;

		// 中心角 [0,2Pi]
		double m_centralAngle;

		// 光源からの光が届く距離 [0, 2Pi] 
		double m_distance;

		// 光の明るさ [0, 1]
		double m_alpha;

	public:

		AccessLight();

	public:

		/// <summary>
		/// 光源の座標の設定
		/// </summary>
		/// <param name="sourcePos"> 光源の座標 </param>
		/// <returns> *this </returns>
		AccessLight& setSourcePos(const Vec2& sourcePos)
		{
			m_sourcePos = sourcePos;
			return *this;
		}

		/// <summary>
		/// 光が差す方向の設定
		/// </summary>
		/// <param name="directionAngle"> 光が差す方向（x軸+の方向を0としたときの左回りの角度 [0, 2Pi]） </param>
		/// <returns> *this </returns>
		AccessLight& setDirectionAngle(double directionAngle)
		{
			m_directionAngle = Clamp(directionAngle, 0.0, Math::TwoPi);
			return *this;
		}

		/// <summary>
		/// 中心角の設定
		/// </summary>
		/// <param name="centralAngle"> 光を扇型としたときの中心角 [0, 2Pi] </param>
		/// <returns> *this </returns>
		AccessLight& setCentralAngle(double centralAngle)
		{
			m_centralAngle = Clamp(centralAngle, 0.0, Math::TwoPi);
			return *this;
		}

		/// <summary>
		/// 距離の設定
		/// </summary>
		/// <param name="distance"> 光源と光が届く最も遠い点の距離 </param>
		/// <returns> *this </returns>
		AccessLight& setDistance(double distance)
		{
			m_distance = Max(0.0, distance);
			return *this;
		}

		/// <summary>
		/// 光の明るさの設定
		/// </summary>
		/// <param name="alpha"> 光の明るさ MyWhiteの不透明度 [0, 1] </param>
		/// <returns> *this </returns>
		AccessLight& setAlpha(double alpha)
		{
			m_alpha = alpha;
			return *this;
		}

		/// <summary>
		/// 更新
		/// </summary>
		/// <param name="terrain"> 地形データ </param>
		void update(const Terrain& terrain);

		/// <summary>
		/// 描画
		/// </summary>
		void draw() const;

	};
}