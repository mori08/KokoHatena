#pragma once

#include<Siv3D.hpp>

namespace Kokoha
{
	/// <summary>
	/// RecordSetの選択/描画
	/// </summary>
	class RecordBox
	{
	private:

		// 座標
		Vec2 m_pos;

		// 座標の移動先
		Vec2 m_goal;

		// 選択されたときの処理
		const std::function<void()> m_onSelected;

		// 表示する文字列
		const std::pair<String, String> m_textPair;

	public:

		/// <param name="onSelected"> 選択されたときの処理 </param>
		/// <param name="itr"> RecordSetのイテレータ </param>
		RecordBox(std::function<void()> onSelected, const std::pair<String, String>& textPair);

		/// <summary>
		/// 更新
		/// </summary>
		void update();

		/// <summary>
		/// 座標の移動先を設定
		/// </summary>
		/// <param name="index"> 表示する順番 </param>
		void setGoalPos(const int32 index);

		/// <summary>
		/// 座標の移動先を設定
		/// </summary>
		/// <param name="pos"> 座標の移動先 </param>
		void setGoalPos(const Vec2& pos);

		/// <summary>
		/// 描画
		/// </summary>
		void draw() const;

		/// <summary>
		/// 描画する範囲（サイズ）の取得
		/// </summary>
		/// <returns> 描画する範囲 </returns>
		static const Size& getSize();

	};
}