﻿#include "RecordSet.hpp"
#include "../../Config/Config.hpp"
#include "../../MyLibrary/MyLibrary.hpp"

namespace
{
	constexpr int32 BASE    = 0x10;        // 暗号化の基準になる値(何進数で暗号化するか)
	constexpr int32 MUL     = BASE - 1;    // 掛け算のときのかける数
	constexpr int32 HALF    = BASE / 2;    // 基準値の半分
	constexpr int32 MOD     = BASE * BASE; // 余りをとるときの割る数 
	constexpr int32 MAX_KEY = MOD - 1;     // 鍵の最大値

	// 暗号文における1データのとる文字数
	constexpr int32 ONE_DATA_LENGTH = 2;

	// 桁の合計値
	int32 totalDigit = 0;
}

namespace Kokoha
{
	const String RecordSet::FILE_NAME = U"YOUR_RECORD";

	RecordSet::RecordSet()
		: m_recordMap(getDefaultRecordMap())
	{
		setRecordTime();
	}

	String RecordSet::encryption() const
	{
		// 暗号用のリスト
		std::list<int32> dataList;

		// 各レコードから 0,1 のリストを追加
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
		const int32 key = Random(0x0, MAX_KEY);

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

	Optional<RecordSet> RecordSet::decryption(const String& str)
	{
		// 復号用のリスト
		std::list<int32> dataList;

		// 文字列 -> 整数値の配列
		for (size_t i = 0; i < str.length(); i += ONE_DATA_LENGTH)
		{
			auto data = ParseIntOpt<int32>(str.substr(i, ONE_DATA_LENGTH), Arg::radix = BASE);
			if (!data)
			{
				return none; // 変換できないとき失敗
			}
			dataList.emplace_back(*data);
		}

		// 前の項の値と mod 0x100 で 減算
		int32 previouseOne = 0;
		for (auto& data : dataList)
		{
			int32 tmp = data;
			data = (data - previouseOne + MOD) % MOD;
			previouseOne = tmp;
		}

		// 先頭・末尾の鍵を削除
		if (*dataList.begin() != *dataList.rbegin())
		{
			return none; // 鍵が一致しないとき失敗
		}
		dataList.pop_front();
		dataList.pop_back();

		// サイズ と レコードの合計桁数 が一致しているか確認
		if (dataList.size() != totalDigit)
		{
			return none; // 一致しないとき失敗
		}

		// 全てを0xFで割る
		for (auto& data : dataList)
		{
			if (data % MUL != 0)
			{
				return none; // 割り切れないとき失敗
			}
			data /= MUL;
			if (data <= 0x0 || data > BASE)
			{
				return none; // [0x1,0x10]の範囲にないとき失敗
			}
		}

		// 偶数 -> 0
		// 奇数 -> 1
		for (auto& data : dataList)
		{
			data %= 2;
		}

		// レコードに格納
		RecordSet rtn;
		for (auto& record : rtn.m_recordMap)
		{
			record.second.setValueFromDecryption(dataList);
		}
		rtn.setTimeCode();

		return rtn;
	}

	RecordSet& RecordSet::setRecord(const String& name, uint32 value)
	{
		if (!m_recordMap.count(name))
		{
			throw Error(U"Faild to find [" + name + U"] record");
		}

		m_recordMap.find(name)->second.set(value);

		return *this;
	}

	RecordSet& RecordSet::setRecordTime()
	{
		const DateTime t = DateTime::Now();

		setRecord(U"RecordYear"  , t.year%100); // 年は2桁に調整
		setRecord(U"RecordMonth" , t.month   );
		setRecord(U"RecordDate"  , t.day     );
		setRecord(U"RecordHour"  , t.hour    );
		setRecord(U"RecordMinute", t.minute  );

		setTimeCode();

		return *this;
	}

	uint32 RecordSet::getRecord(const String& name) const
	{
		if (!m_recordMap.count(name))
		{
			throw Error(U"Faild to find [" + name + U"] record");
		}

		return m_recordMap.find(name)->second.get();
	}

	void RecordSet::writeDebugText() const
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

	void RecordSet::setTimeCode()
	{
		// 2桁で文字列化(1桁の数値の場合は0で埋める)
		constexpr std::pair<int32, char32> PADDING = { 2,U'0' };

		m_timeCode
			= Pad(getRecord(U"RecordYear"  ), PADDING) + U":"
			+ Pad(getRecord(U"RecordMonth" ), PADDING) + U":"
			+ Pad(getRecord(U"RecordDate"  ), PADDING) + U":"
			+ Pad(getRecord(U"RecordHour"  ), PADDING) + U":"
			+ Pad(getRecord(U"RecordMinute"), PADDING);
	}

	const std::map<String, Record>& RecordSet::getDefaultRecordMap() const
	{
		// 一度TOMLファイルを読み込んだらtrueにする
		static bool isReady = false;
		// Recordのマップ
		static std::map<String, Record> defaultMap;

		if (isReady) { return defaultMap; }

		// Recordについてのtomlファイル
		const TOMLReader m_toml(U"asset/data/record.toml");
		totalDigit = 0;

		for (const auto& obj : m_toml[U"Record"].tableArrayView())
		{
			defaultMap.try_emplace
			(
				obj[U"name"].getString(),
				std::move(Record(obj[U"digit"].get<int32>(), obj[U"default"].get<int32>()))
			);

			totalDigit += obj[U"digit"].get<int32>();
		}
		isReady = true;
		return defaultMap;
	}
}
