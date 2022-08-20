#pragma once

#include"Record/Record.hpp"

namespace Kokoha
{
	/// <summary>
	/// 複数のRecordを管理し、
	/// 文字列との変換、各Recordの変更/取得を行う
	/// </summary>
	class RecordSet
	{
	public:

		// レコードを保存するファイル名
		static const String FILE_NAME;

	private:

		// Recordのマップ
		std::map<String, Record> m_recordMap;

		// 時間を表す文字列
		String m_timeCode;

	public:

		/// <summary>
		/// Recordをデフォルト値で設定
		/// </summary>
		RecordSet();

		/// <summary>
		/// 暗号文を復号し、フラグのリストに格納する
		/// </summary>
		/// <param name="str"> 暗号化された文字列 </param>
		static Optional<RecordSet> decryption(const String& str);

		/// <summary>
		/// レコードの暗号化
		/// </summary>
		/// <returns> 暗号化した文字列 </returns>
		String encryption() const;

		/// <summary>
		/// レコードの設定
		/// </summary>
		/// <param name="name"> 名前 </param>
		/// <param name="value"> 変更後の値 </param>
		/// <returns> *this </returns>
		RecordSet& setRecord(const String& name, int32 value);

		/// <summary>
		/// レコードに現在の時刻を設定する
		/// </summary>
		/// <returns> *this </returns>
		RecordSet& setRecordTime();

		/// <summary>
		/// レコードの取得
		/// </summary>
		/// <param name="name"> 名前 </param>
		/// <returns> レコードの値 </returns>
		int32 getRecord(const String& name) const;

		/// <summary>
		/// 描画
		/// </summary>
		/// <param name="pos"> 座標 </param>
		void draw(const Point& pos) const;

		/// <summary>
		/// テキストファイルにレコードの内容を書き込み
		/// </summary>
		void writeDebugText() const;

	private:

		/// <summary>
		/// 初期値を格納したRecordのマップを取得（初回のみTOMLファイルの読み込み）
		/// </summary>
		/// <returns> 初期値を格納したRecordのマップ </returns>
		const std::map<String, Record>& getDefaultRecordMap() const;

	};
}