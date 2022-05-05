#include "RecordManager.hpp"


namespace
{
	// レコードを保存するファイル名
	const String RECORD_TEXT_NAME = U"YOUR_RECORD.txt";

	constexpr int32 BASE    = 0x10;        // 暗号化の基準になる値(何進数で暗号化するか)
	constexpr int32 MUL     = BASE - 1;    // 掛け算のときのかける数
	constexpr int32 HALF    = BASE / 2;    // 基準値の半分
	constexpr int32 MOD     = BASE * BASE; // 余りをとるときの割る数 
	constexpr int32 MAX_KEY = MOD - 1;     // 鍵の最大値

	// 暗号文における1データのとる文字数
	constexpr int32 ONE_DATA_LENGTH = 2;
}


namespace Kokoha
{
	RecordManager::RecordManager()
		: m_totalDigit(setAllRecordToMap())
	{
	}

	int32 RecordManager::setAllRecordToMap()
	{
		const TOMLReader m_toml(U"asset/data/record.toml");

		// 桁数の合計
		int32 totalDigit = 0;

		for (const auto& obj : m_toml[U"Record"].tableArrayView())
		{
			m_recordMap.try_emplace
			(
				obj[U"name"].getString(),
				std::move(Record(obj[U"digit"].get<int32>(), obj[U"default"].get<int32>()))
			);

			totalDigit += obj[U"digit"].get<int32>();
		}

		return totalDigit;
	}

    Kokoha::RecordManager::LoadResult Kokoha::RecordManager::load()
    {
		TextReader reader(RECORD_TEXT_NAME);

		// セーブデータ用ファイルがないとき NEWGAME
		if (!reader)
		{
			initAllRecord();
			return LoadResult::NEW_GAME;
		}

		String line;

		if (reader.readLine(line) && decryption(line))
		{
			// 復号できたら CONTINUE
			return LoadResult::LOAD_GAME;
		}

		return LoadResult::ERROR;
    }


	void RecordManager::initAllRecord()
	{
		for (auto& record : m_recordMap)
		{
			record.second.init();
		}
	}


	void RecordManager::save()
	{
		TextWriter writer(RECORD_TEXT_NAME);

		writer.write(encryption());
	}


	void RecordManager::setRecord(const String& name, int32 value)
	{
		if (!m_recordMap.count(name))
		{
			throw Error(U"Faild to find [" + name + U"] record");
		}

		m_recordMap.find(name)->second.set(value);
	}


	int32 RecordManager::getRecord(const String& name) const
	{
		if (!m_recordMap.count(name))
		{
			throw Error(U"Faild to find [" + name + U"] record");
		}

		return m_recordMap.find(name)->second.get();
	}


	String RecordManager::encryption() const
	{
		// 暗号用のリスト
		std::list<int32> dataList;

		// 各レコードから 0 1 のリストを追加
		for (const auto& record : m_recordMap)
		{
			record.second.addRecordToEncryptionList(dataList);
		}

		// 0 -> [0x2,0x10]の範囲の偶数
		// 1 -> [0x1,0xF] の範囲の奇数
		for (auto& data : dataList)
		{
			data = 2 * (Random(0x1, HALF)) - data;
		}

		// 全てを0xFかける
		for (auto& data : dataList)
		{
			data *= MUL;
		}

		// 鍵を生成する 
		int32 key = Random(0x0, MAX_KEY);

		// リストの先頭と末尾に鍵を追加
		dataList.emplace_front(key);
		dataList.emplace_back(key);

		// 前の項の値を mod 0x100 で加算
		int32 previousOne = 0;
		for (auto& data : dataList)
		{
			data = (data + previousOne) % MOD;
			previousOne = data;
		}

		// 整数値の配列 -> 文字列
		String rtn;
		for (const auto& data : dataList)
		{
			rtn += Pad(U"{:x}"_fmt(data), { ONE_DATA_LENGTH, U'0' });
		}

		return rtn;
	}


	bool RecordManager::decryption(const String& str)
	{
		// 復号用のリスト
		std::list<int32> dataList;

		// 文字列 -> 整数値の配列
		for (size_t i = 0; i < str.length(); i += ONE_DATA_LENGTH)
		{
			auto data = ParseIntOpt<int32>(str.substr(i, ONE_DATA_LENGTH), Arg::radix = BASE);
			if (!data)
			{
				return false; // 変換できないとき失敗
			}
			dataList.emplace_back(*data);
		}

		// 前の項の値と mod 0x100 で 減算
		int32 previouseOne = 0;
		for (auto& data : dataList)
		{
			int32 temp = data;
			data = (data - previouseOne + MOD) % MOD;
			previouseOne = temp;
		}

		// 先頭・末尾の鍵を削除
		if (*dataList.begin() != *dataList.rbegin())
		{
			return false; // 鍵が一致しないとき失敗
		}
		dataList.pop_front();
		dataList.pop_back();

		// サイズ と レコードの合計桁数 が一致しているか確認
		if (dataList.size() != m_totalDigit)
		{
			return false; // 一致しないとき失敗
		}

		// 全てを0xFで割る
		for (auto& data : dataList)
		{
			if (data % MUL != 0)
			{
				return false; // 割り切れないとき失敗
			}
			data /= MUL;
			if (data <= 0x0 || data > BASE)
			{
				return false; // [0x1,0x10]の範囲にないとき失敗
			}
		}

		// 偶数 -> 0
		// 奇数 -> 1
		for (auto& data : dataList)
		{
			data %= 2;
		}

		// レコードに格納
		for (auto& record : m_recordMap)
		{
			record.second.setValueFromDecryption(dataList);
		}

		return true;
	}

}
