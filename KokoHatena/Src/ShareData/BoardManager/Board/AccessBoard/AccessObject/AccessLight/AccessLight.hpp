#pragma once

#include "../../Terrain/Terrain.hpp"
#include "PolarLine/PolarLine.hpp"

namespace Kokoha
{
	/// <summary>
	/// AccessObjectが所有する光
	/// </summary>
	class AccessLight
	{
	private: // 光の条件

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

		// 光の色
		ColorF m_color;

		// trueのときのみ影の計算を行う
		bool m_shadowMode;

		// 光を表す多角形
		Polygon m_polygon;

	private: // 光作成時に使用

		/// <summary>
		/// 角度ごとの行う処理
		/// </summary>
		class AngleEvent
		{
		public:
			double angle; // 角度
			std::function<void()> func; // 処理
			AngleEvent(double a, std::function<void()> f) : angle(a), func(f) {}
			bool operator<(const AngleEvent& another) const { return angle > another.angle; }
		};

		// true のとき 扇型 , false のとき 円形
		bool m_isPie;

		// 頂点配列
		Array<Vec2> m_posAry;

		// 辺配列
		Array<PolarLine> m_edgeAry;

		// 辺のヒープ 最も光源に近い辺を取得できる
		Array<size_t> m_heap;

		// 辺番号 -> 木番号
		Array<size_t> m_edgeToHeap;

	public:

		AccessLight();

	public:

		/// <summary>
		/// 点灯する
		/// </summary>
		/// <returns> *this </returns>
		AccessLight& on()
		{
			m_on = true;
			return *this;
		}

		/// <summary>
		/// 消灯する
		/// </summary>
		/// <returns> *this </returns>
		AccessLight& off()
		{
			m_on = false;
			return *this;
		}

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
		/// <param name="rate"> 遷移の割合 </param>
		/// <returns> *this </returns>
		AccessLight& setDirectionAngle(double directionAngle, double rate = 0);

		/// <summary>
		/// 中心角の設定
		/// </summary>
		/// <param name="centralAngle"> 光を扇型としたときの中心角 [0, 2Pi] </param>
		/// <param name="rate"> 遷移の割合 </param>
		/// <returns> *this </returns>
		AccessLight& setCentralAngle(double centralAngle, double rate = 0);

		/// <summary>
		/// 距離の設定
		/// </summary>
		/// <param name="distance"> 光源と光が届く最も遠い点の距離 </param>
		/// <param name="rate"> 割合の遷移 </param>
		/// <returns> *this </returns>
		AccessLight& setDistance(double distance, double rate = 0);

		/// <summary>
		/// 光の面積から距離の設定
		/// </summary>
		/// <param name="area"> 影を考慮しない光の面積 </param>
		/// <param name="rate"> 割合の遷移 </param>
		/// <returns> *this </returns>
		AccessLight& setDistanceFromArea(double area, double rate = 0);

		/// <summary>
		/// 光の色を設定
		/// </summary>
		/// <param name="color"> 色を設定 </param>
		/// <returns> *this </returns>
		AccessLight& setColor(const ColorF& color)
		{
			m_color = color;
			return *this;
		}

		/// <summary>
		/// 光の明るさの設定
		/// </summary>
		/// <param name="alpha"> 光の明るさ MyWhiteの不透明度 [0, 1] </param>
		/// <returns> *this </returns>
		AccessLight& setAlpha(double alpha, double rate = 0);

		/// <summary>
		/// 影の計算についての設定
		/// </summary>
		/// <param name="shadowMode"> trueのとき影の計算を行う , falseのときは円or扇形をそのまま描画 </param>
		/// <returns> *this </returns>
		AccessLight& setShadowMode(bool shadowMode)
		{
			m_shadowMode = shadowMode;
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

		/// <summary>
		/// 面積の取得
		/// </summary>
		/// <returns> 面積 </returns>
		double area() const;

		/// <summary>
		/// 指定された座標を含んでいるか
		/// </summary>
		/// <param name="pos"> 座標 </param>
		/// <returns> true のとき指定された座標が含まれている </returns>
		bool contains(const Vec2& pos);

	private:

		/// <summary>
		/// 距離がm_distanceの座標を追加
		/// </summary>
		/// <param name="angle"> 角度 </param>
		void addPoint(double angle);

		/// <summary>
		/// 扇型の端の点の追加
		/// </summary>
		/// <param name="angle"> 角度 </param>
		void addPiePoint(double angle);

		/// <summary>
		/// 辺の始点の追加
		/// </summary>
		/// <param name="edgeId"> 辺番号 </param>
		void addStartPoint(size_t edgeId);

		/// <summary>
		/// 辺の終点の追加
		/// </summary>
		/// <param name="edgeId"> 辺番号 </param>
		void addEndPoint(size_t edgeId);

		/// <summary>
		/// ヒープ先頭の辺を取得
		/// </summary>
		/// <param name="angle"> 角度 </param>
		/// <returns> ヒープ先頭の辺の角度に対応する点の動径 </returns>
		double heapTopR(double angle) const;

		/// <summary>
		/// ヒープに辺を追加
		/// </summary>
		/// <param name="edgeId"> 辺番号 </param>
		/// <param name="angle"> 角度 </param>
		void addEdgeToHeap(size_t edgeId, double angle);

		/// <summary>
		/// ヒープから辺を削除
		/// </summary>
		/// <param name="edgeId"> 辺番号 </param>
		/// <param name="angle"> 角度 </param>
		void removeEdgeToHeap(size_t edgeId, double angle);

		/// <summary>
		/// 頂点を逆転がなくなるまで上へ上げる
		/// </summary>
		/// <param name="i"> 木番号 </param>
		/// <param name="angle"> 角度 </param>
		void heapUp(size_t i, double angle);

		/// <summary>
		/// 頂点を逆転がなくなるまで下へ下げる
		/// </summary>
		/// <param name="i"> 木番号 </param>
		/// <param name="angle"> 角度 </param>
		void heapDown(size_t i, double angle);

		/// <summary>
		/// 辺の比較
		/// </summary>
		/// <param name="id1"> 木番号1 </param>
		/// <param name="id2"> 木番号2 </param>
		/// <param name="angle"> 角度 </param>
		/// <returns> 辺1が辺2より手前にある場合 true , そうでないとき false </returns>
		bool compareEdge(size_t edgeId1, size_t edgeId2, double angle) const;

	};
}
