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
	private:

		// Recordのマップ
		std::map<String, Record> m_recordMap;

		// 読み込みに失敗しているとき true , そうでないとき false
		bool m_isError;

	public:

		/// <summary>
		/// Recordをデフォルト値で設定
		/// </summary>
		RecordSet();

		/// <summary>
		/// 文字列を復号しRecordに設定
		/// </summary>
		/// <param name="text"></param>
		RecordSet(const String& str);

		/// <summary>
		/// 文字列への変換
		/// </summary>
		/// <returns> エラーなら none , そうでないなら暗号化した文字列 </returns>
		Optional<String> toString() const;

		/// <summary>
		/// レコードの設定
		/// </summary>
		/// <param name="name"> 名前 </param>
		/// <param name="value"> 変更後の値 </param>
		void setRecord(const String& name, int32 value);

		/// <summary>
		/// レコードの取得
		/// </summary>
		/// <param name="name"> 名前 </param>
		/// <returns> レコードの値 </returns>
		int32 getRecord(const String& name) const;

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

		/// <summary>
		/// レコードの暗号化
		/// </summary>
		/// <returns> 暗号化した </returns>
		String encryption() const;

		/// <summary>
		/// 暗号文を復号し、フラグのリストに格納する
		/// </summary>
		/// <param name="str"></param>
		void decryption(const String& str);

	};
}