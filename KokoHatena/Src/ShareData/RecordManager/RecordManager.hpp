#pragma once

#include "Record/Record.hpp"

namespace Kokoha
{
	/// <summary>
	/// レコード（セーブデータ）のロードやセーブ，
	/// フラグや数値の変更，取得を行う
	/// </summary>
	class RecordManager
	{
	public:

		enum class LoadResult
		{
			NEW_GAME,  // YOUR_RECORD.txtが存在しないとき
			LOAD_GAME, // YOUR_RECORD.txtを正しく読み込めたとき
			ERROR      // YOUR_RECORD.txtが読み込めなかったとき
		};

	private:

		// レコードのマップ
		std::map<String, Record> m_recordMap;

		// 桁数の合計
		const int32 m_totalDigit;

	public:

		RecordManager();

		/// <summary>
		/// セーブデータ用ファイルからロード
		/// </summary>
		/// <returns> ロードの結果 </returns>
		LoadResult load();

		/// <summary>
		/// 全レコードの初期化
		/// </summary>
		void initAllRecord();

		/// <summary>
		/// セーブデータ用ファイルにセーブ
		/// </summary>
		void save();

		/// <summary>
		/// レコードの設定
		/// </summary>
		/// <param name="name" > 名前         </param>
		/// <param name="value"> 変更したい値 </param>
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
		void writeDebugText() const
		{
#ifdef _DEBUG
			TextWriter writer(U"asset/data/debug.txt");
			char32 initChar = U'z';
			for (const auto& record : m_recordMap)
			{
				if (record.first[0] != initChar)
				{
					initChar = record.first[0];
					writer.writeln(String(U"\n[ ") + initChar + U" ]");
				}
				writer.writeln(Pad(ToString(record.second.get()), { 4,U' ' }) + U" < [" + record.first + U"]");
			}
			writer.close();
#endif // _DEBUG
		}

	private:

		/// <summary>
		/// m_recordMapに必要となるRecordを全て登録
		/// </summary>
		/// <returns> 合計桁数 </returns>
		int32 setAllRecordToMap();

		/// <summary>
		/// レコードの暗号化
		/// </summary>
		/// <returns> 暗号化した </returns>
		String encryption() const;

		/// <summary>
		/// 暗号文を復号，フラグのリストに格納
		/// </summary>
		/// <param name="str"> 暗号文 </param>
		/// <returns> 復号に成功したとき true , そうでないとき false </returns>
		bool decryption(const String& str);

	};
}