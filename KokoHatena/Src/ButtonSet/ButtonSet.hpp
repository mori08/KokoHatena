#pragma once

#include "Button/Button.hpp"

namespace Kokoha
{
	/// <summary>
	/// Buttonクラスのリストを扱い
	/// 更新や削除を行う
	/// </summary>
	class ButtonSet
	{
	private:

		// 管理しているボタンの連想配列
		std::unordered_map<String, Button> m_buttonMap;

		// 選択中のボタンの名前
		String m_selectedButtonName;

	public:

		/// <summary>
		/// ボタンの登録
		/// </summary>
		/// <param name="name"  > ボタンの名前 </param>
		/// <param name="region"> ボタンの範囲 </param>
		void registerButton(const String& name, const Rect& region);

		/// <summary>
		/// ボタンの登録
		/// </summary>
		/// <param name="button"> ボタン </param>
		void registerButton(const Button& button);

		/// <summary>
		/// 選択中のボタンの変更
		/// </summary>
		/// <param name="name"> ボタンの名前 </param>
		void setSelectedButton(const String& name);

		/// <summary>
		/// ボタンを押したときの処理の設定
		/// </summary>
		/// <param name="name">        ボタンの名前     </param>
		/// <param name="onClickFunc"> 押したときの処理 </param>
		void setOnClickFunc(const String& name, std::function<void()> onClickFunc);

		/// <summary>
		/// ボタンのリストの取得
		/// </summary>
		/// <returns> ボタンのリスト </returns>
		const std::unordered_map<String, Button>& getButtonList() const
		{
			return m_buttonMap;
		}

		/// <summary>
		/// 選択中のボタンの取得
		/// </summary>
		/// <returns> 選択中のボタン </returns>
		const Button& getSelectedButton() const;

		/// <summary>
		/// ボタンの削除
		/// </summary>
		/// <param name="name"> 削除するボタンの名前 </param>
		void eraseButton(const String& name);

		/// <summary>
		/// ボタンのリストを空にします
		/// </summary>
		void clearButtonList();

		/// <summary>
		/// ボタンの選択及びボタンを押されたときの処理の呼び出し
		/// </summary>
		/// <param name="basePos"> 基準座標 </param>
		/// <returns> 選択しているボタンが変更されたとき true , そうでないとき false </returns>
		/// <remarks>
		/// 入力に応じたボタン選択の変更と
		/// 決定キーが押されたときそのボタンのOnClick関数を呼ぶ
		/// 1フレームに2度以上使わない
		/// </remarks>
		bool update(const Point& basePos = Point::Zero());

	};
}
