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

		// RecordBoxを選択した場合に遷移するシーン
		const SceneName m_sceneName;

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
			const RecordBox& recordBox, 
			std::function<void(const RecordSet&)> recordFunc, 
			const String& explanation,
			SceneName sceneName);

	protected:

		virtual void update() override;

		virtual void draw() const override;
	};

	/// <summary>
	/// ロードするRecordSetを登録する
	/// </summary>
	class SelectLoadRecordScene : public SelectRecordScene
	{
	public:
		SelectLoadRecordScene(const InitData& init);
	};
}