#pragma once

#include<Siv3D.hpp>

namespace Kokoha
{
	// 画像の切り替え順              時間    座標
	using PosOrder = Array<std::pair<double, Point>>;

	/// <summary>
	/// Animationクラス
	/// 画像の切り替え順とそれにかかる時間をまとめたもの
	/// </summary>
	class Animation
	{
	private:

		// 画像を切り替え終わるまでにかかる時間
		const double m_totalSecond;

		// 画像の切り替え順
		const PosOrder m_posOrder;

		// true ループする , false 最後の座標で停止
		const bool m_isLoop;

	public:

		/// <summary>
		/// 画像の切り替え順とそれにかかる時間など
		/// </summary>
		/// <param name="posList"> 画像の切り替え順 </param>
		/// <param name="posList"> ループ           </param>
		Animation(const PosOrder& posOrder, bool isLoop);

		/// <summary>
		/// 画像の座標を取得
		/// </summary>
		/// <param name="animSecond"> 時間 </param>
		/// <returns> 時間に対応した画像番号 </returns>
		/// <remarks>
		/// O(log|m_posOrderのサイズ|)時間必要
		/// 対数時間なので大した時間を要しないが
		/// 一応，O(1)でないことに注意
		/// </remarks>
		Point getTexturePos(double animSecond) const;

		/// <summary>
		/// 画像を切り替え終わるまでにかかる時間の取得
		/// </summary>
		/// <returns> 画像を切り替え終わるまでにかかる時間 </returns>
		double getTotalSecond() const
		{
			return m_totalSecond;
		}

		/// <summary>
		/// ループするか示す
		/// </summary>
		/// <returns> ループするとき true , そうでないとき false </returns>
		bool loop() const
		{
			return m_isLoop;
		}

	private:

		/// <summary>
		/// m_totalSecondの計算
		/// </summary>
		static double getTotalSecond(const PosOrder& posOrder);

		/// <summary>
		/// m_posOrderの時間を累計に変更
		/// </summary>
		static PosOrder getPosOrder(PosOrder posOrder);

	};
}