#pragma once

#include "../Scene.hpp"
#include "RecordBox/RecordBox.hpp"

namespace Kokoha
{
	/// <summary>
	/// RecordBoxを選択するシーン
	/// 選択したRecordSetをどうするかは派生クラスで決定される
	/// </summary>
	class SelectRecordScene : public MyApp::Scene
	{
	protected:

		// このシーンの説明文
		const String m_explanation;

		// RecordBoxのリスト
		std::list<RecordBox> m_recordBoxList;

		// 画面内の一番上に表示するRecordBoxのイテレータ
		std::list<RecordBox>::iterator m_topBoxItr;

		// スクロールバーを表示するy座標
		double m_scrollBarPosY;

		// マウスホイールでのスクロール時のクールタイム
		double m_wheel;

	public:

		/// <summary>
		/// RecordBoxを選択するシーン
		/// </summary>
		/// <param name="recordBox"> 一番上に表示するRecordBox </param>
		/// <param name="recordFunc"> RecordSetに対応する処理 </param>
		/// <param name="explanation"> シーンの説明文 </param>
		/// <param name="sceneName"> 選択時に遷移するシーン名 </param>
		SelectRecordScene(
			const InitData& init, 
			const String& explanation
		);

	protected:

		/// <summary>
		/// 初期化用関数
		/// 派生クラスでm_recordBoxListを作成した後に呼ぶ
		/// </summary>
		void initRecordBox();

		virtual void update() override;

		virtual void draw() const override;

	private:

		/// <summary>
		/// スクロールホイールでのRecordBoxの移動
		/// </summary>
		void scrollWheel();

	};

	/// <summary>
	/// ロードするRecordSetを選択する
	/// </summary>
	class SelectLoadRecordScene : public SelectRecordScene
	{
	public:
		SelectLoadRecordScene(const InitData& init);
	};

	/// <summary>
	/// セーブするRecordSetを選択する
	/// </summary>
	class SelectSaveRecordScene : public SelectRecordScene
	{
	public:
		SelectSaveRecordScene(const InitData& init);
	};
}
