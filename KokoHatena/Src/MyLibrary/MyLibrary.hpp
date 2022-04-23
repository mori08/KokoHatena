#pragma once


#include <Siv3D.hpp>


namespace Kokoha
{
	// 黒
	constexpr ColorF MyBlack(Color(0x0F));

	// 白
	constexpr ColorF MyWhite(Color(0xF0));

	/// <summary>
	/// 色の出力
	/// </summary>
	/// <param name="rgb"  > rgbの値 [0,1] </param>
	/// <param name="alpha"> 不透明度[0,1] </param>
	constexpr inline ColorF myColor(double rgb, double alpha = 1.0)
	{
		return ColorF(Max(0.0, Min(1.0, rgb)) * (MyWhite.r - MyBlack.r) + MyBlack.r, alpha);
	}


#ifdef _DEBUG
	/// <summary>
	/// デバッグ用の文字列を出力
	/// </summary>
	/// <param name="message"> 出力する文字列 </param>
	inline void printDebug(const String& message)
	{
		Print << message;
	}
#else
	inline void printDebug(const String&)
	{

	}
#endif // _DEBUG

	/// <summary>
	/// アセット管理
	/// </summary>
	/// <param name="direName"> ディレクトリの名前 </param>
	void registerAsset(const String& dirName);

	/// <summary>
	/// 指定された頻度でランダムに 1 を出力
	/// </summary>
	/// <param name="frequency"> 頻度 (times/second) </param>
	/// <returns> 
	/// ランダムで 1 または 0 
	/// </returns>
	/// <remarks>
	/// 頻度がフレームレートを超えたとき, 毎フレーム 1 を出力
	/// </remarks>
	inline int32 randomFrequency(double frequency)
	{
		return (Random(1.0 / Scene::DeltaTime()) < frequency) ? 1 : 0;
	}

	/// <summary>
	/// 内分点を使った値の変更
	/// </summary>
	/// <param name="x"> 変更したい値     </param>
	/// <param name="a"> 目的値           </param>
	/// <param name="r"> 内分比(0,1) (/s) </param>
	/// <remarks>
	/// r には (0,1)の範囲の小数値
	/// 数値は0に近づけるほど速く移動
	/// </remarks>
	template<typename TYPE_X, typename TYPE_A>
	void internalDividingPoint(TYPE_X& x, const TYPE_A& a, double r)
	{
		r = Pow(r, Scene::DeltaTime());
		x = r * x + (1 - r) * a;
	}

	/// <summary>
	/// FPSの表示
	/// </summary>
	void showFPS();

	/// <summary>
	/// 中心座標を決めた長方形の取得
	/// </summary>
	/// <param name="center"> 中心座標 </param>
	/// <param name="size">   サイズ   </param>
	/// <returns> 長方形 </returns>
	inline constexpr Rect getRectFromCenter(const Point& center, const Size& size)
	{
		return std::move(Rect(center - size / 2, size));
	}

	/// <summary>
	/// 2頂点から長方形の取得
	/// </summary>
	/// <param name="pos1"> 頂点1 </param>
	/// <param name="pos2"> 頂点2 </param>
	/// <returns> 長方形 </returns>
	inline constexpr Rect getRectFromTwoPoint(const Point& pos1, const Point& pos2)
	{
		return std::move(Rect(Min(pos1.x, pos2.x), Min(pos1.y, pos2.y), Abs(pos1.x - pos2.x), Abs(pos1.y - pos2.y)));
	}

	/// <summary>
	/// 長方形の頂点リストを取得
	/// </summary>
	/// <param name="rect"> 長方形 </param>
	/// <returns> 頂点リスト </returns>
	inline const Array<Vec2> getRectNode(const RectF& rect)
	{
		return { rect.tl(),rect.tr(),rect.br(),rect.bl() };
	}

	/// <summary>
	/// 長方形の辺リストを取得
	/// </summary>
	/// <param name="rect"> 長方形 </param>
	/// <returns> 頂点リスト </returns>
	inline const Array<Line> getRectEdge(const RectF& rect)
	{
		return { rect.top(),rect.right(),rect.bottom(),rect.left() };
	}

	/// <summary>
	/// 長方形内にある格子点のリストの取得
	/// </summary>
	/// <param name="rect"> 長方形 </param>
	/// <returns> 格子点 </returns>
	Array<Point> getGridPoint(const Rect& rect);

	/// <summary>
	/// 角度からその方向を向いた単位ベクトルを取得
	/// </summary>
	/// <param name="angle"> 角度(rad) </param>
	/// <returns> 単位ベクトル </returns>
	/// <remarks>
	/// 0(rad)をベクトル(1,0)に対応させ，
	/// 時計回りを正の方向とする
	/// </remarks>
	inline constexpr Vec2 angleToVec(double angle)
	{
		return std::move(Vec2(Cos(angle), Sin(angle)));
	}

	/// <summary>
	/// 2ベクトルがなす角度を取得
	/// </summary>
	/// <param name="v1"> ベクトル1 </param>
	/// <param name="v2"> ベクトル2 </param>
	/// <returns> 角度(rad) [-Pi,Pi) </returns>
	/// <remarks>
	/// ベクトル1を基準にして時計回りを正として計算
	/// </remarks>
	inline double twoVecToAngle(Vec2 v1, Vec2 v2)
	{
		v1.normalize(); v2.normalize();
		return Acos(Clamp(v1.dot(v2), -1.0, 1.0)) * (v1.x * v2.y - v1.y * v2.x > 0 ? 1 : -1);
	}

	/// <summary>
	/// ベクトルがx軸となす角度を取得
	/// </summary>
	/// <param name="v"> ベクトル </param>
	/// <returns> 角度(rad) [-Pi,Pi) </returns>
	/// <remarks>
	/// ベクトル1を基準にして時計回りを正として計算
	/// </remarks>
	inline double vecToAngle(const Vec2& v)
	{
		return twoVecToAngle(Vec2(1, 0), v);
	}

	/// <summary>
	/// デバッグ用動作
	/// </summary>
	/// <returns> 移動量 </returns>
	inline Point debugMovement()
	{
		return Point(KeyD.pressed() - KeyA.pressed(), KeyS.pressed() - KeyW.pressed())
			+ Point(KeyRight.down() - KeyLeft.down(), KeyDown.down() - KeyUp.down());
	}


}