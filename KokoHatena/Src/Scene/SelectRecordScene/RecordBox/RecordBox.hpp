#pragma once

#include "../../SceneName.hpp"

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

		// 幅
		double m_width;

		// 座標の移動先
		Vec2 m_goal;

		// 選択されたときの処理
		const std::function<SceneName()> m_onSelected;

		// 表示する文字列
		const std::pair<String, String> m_textPair;

	public:

		/// <param name="onSelected"> 選択されたときの処理 </param>
		/// <param name="itr"> RecordSetのイテレータ </param>
		RecordBox(std::function<SceneName()> onSelected, const std::pair<String, String>& textPair);

		/// <summary>
		/// 更新
		/// </summary>
		/// <returns> 選択されたとき 遷移先のSceneName , そうでないとき none </returns>
		Optional<SceneName> update();

		/// <summary>
		/// 移動先の座標を取得
		/// </summary>
		/// <param name="index"> 表示する順番 </param>
		/// <returns> 
		Vec2 getPos(int32 index) const;

		/// <summary>
		/// 座標を設定
		/// </summary>
		/// <param name="index"> 表示する順番 </param>
		void setPos(const int32 index);

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

	private:

		/// <summary>
		/// 幅の更新
		/// </summary>
		void updateWidth();

	};
}
