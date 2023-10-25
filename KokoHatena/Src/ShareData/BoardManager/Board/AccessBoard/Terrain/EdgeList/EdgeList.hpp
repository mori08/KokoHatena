#pragma once

#include <Siv3D.hpp>

namespace Kokoha
{
	/// <summary>
	/// 辺を作成するための辺のリスト
	/// </summary>
	class EdgeList
	{
	public:

		// 辺 
		// 垂直な辺の場合 {x, {y1, y2}}
		// 水平な辺の場合 {y, {x1, x2}}
		using Edge = std::pair<int32, std::pair<int32, int32>>;

		// 辺のイテレータ
		using ConstItr = std::list<Edge>::const_iterator;

		// 部分リスト
		class SubList
		{
		private:

			ConstItr m_beginItr, m_endItr;

		public:

			SubList(ConstItr beginItr, ConstItr endItr) 
				: m_beginItr(beginItr)
				, m_endItr(endItr) 
			{}

			ConstItr begin() const { return m_beginItr; }
			ConstItr end() const { return m_endItr; }
		};

	private:

		// 辺リスト
		// 配列を使うとエラー
		std::list<Edge> m_edgeList;

		// イテレータの配列
		Array<ConstItr> m_itrAry;

	public:

		/// <summary>
		/// 辺の追加
		/// </summary>
		/// <param name="edge"> 辺 </param>
		void addEdge(const Edge& edge)
		{
			m_edgeList.emplace_back(edge);
		}

		/// <summary>
		/// イテレータの配列を設定
		/// </summary>
		/// <param name="size"> イテレータの配列のサイズ </param>
		void setIteratorAry(int32 size);

		/// <summary>
		/// 範囲内の部分リストを取得
		/// </summary>
		/// <param name="l"> 範囲 （垂直な辺ならx座標 , 水平な辺ならy座標） </param>
		/// <returns> 部分リスト </returns>
		SubList getSubList(const std::pair<int32, int32>& region) const
		{
			return SubList(getItr(region.first), getItr(region.second));
		}

	private:

		/// <summary>
		/// マス座標からイテレータの取得
		/// </summary>
		/// <param name="x"> 垂直な辺ならx座標 , 水平な辺ならy座標 </param>
		/// <returns> 指定のマス座標から見た一番小さい座標の辺 </returns>
		ConstItr getItr(int32 x) const;
	};
}
