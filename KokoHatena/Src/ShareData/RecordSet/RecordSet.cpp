#include "RecordSet.hpp"

namespace
{
	// ���R�[�h��ۑ�����t�@�C����
	const String RECORD_TEXT_NAME = U"YOUR_RECORD.txt";

	constexpr int32 BASE    = 0x10;        // �Í����̊�ɂȂ�l(���i���ňÍ������邩)
	constexpr int32 MUL     = BASE - 1;    // �|���Z�̂Ƃ��̂����鐔
	constexpr int32 HALF    = BASE / 2;    // ��l�̔���
	constexpr int32 MOD     = BASE * BASE; // �]����Ƃ�Ƃ��̊��鐔 
	constexpr int32 MAX_KEY = MOD - 1;     // ���̍ő�l

	// �Í����ɂ�����1�f�[�^�̂Ƃ镶����
	constexpr int32 ONE_DATA_LENGTH = 2;

	// ���̍��v�l
	int32 totalDigit = 0;
}

namespace Kokoha
{
	RecordSet::RecordSet()
		: m_recordMap(getDefaultRecordMap())
		, m_isError(false)
	{
	}

	RecordSet::RecordSet(const String& str)
		: m_recordMap(getDefaultRecordMap())
	{
		decryption(str);
	}

	Optional<String> RecordSet::toString() const
	{
		if (m_isError) { return none; }
		return encryption();
	}

	void RecordSet::setRecord(const String& name, int32 value)
	{
		if (!m_recordMap.count(name) || m_isError)
		{
			throw Error(U"Faild to find [" + name + U"] record");
		}

		m_recordMap.find(name)->second.set(value);
	}

	int32 RecordSet::getRecord(const String& name) const
	{
		if (!m_recordMap.count(name) || m_isError)
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

	const std::map<String, Record>& RecordSet::getDefaultRecordMap() const
	{
		// ��xTOML�t�@�C����ǂݍ��񂾂�true�ɂ���
		static bool isReady = false;
		// Record�̃}�b�v
		static std::map<String, Record> defaultMap;

		if (isReady) { return defaultMap; }

		// Record�ɂ��Ă�toml�t�@�C��
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

	String RecordSet::encryption() const
	{
		// �Í��p�̃��X�g
		std::list<int32> dataList;

		// �e���R�[�h���� 0,1 �̃��X�g��ǉ�
		for (const auto& record : m_recordMap)
		{
			record.second.addRecordToEncryptionList(dataList);
		}

		// 0 -> [0x2,0x10]�͈̔͂̋���
		// 1 -> [0x1,0xF] �͈̔͂̊
		for (auto& data : dataList)
		{
			data = 2 * (Random(0x1, HALF)) - data;
		}

		// �S�Ă�0xF������
		for (auto& data : dataList)
		{
			data *= MUL;
		}

		// ���𐶐����� 
		const int32 key = Random(0x0, MAX_KEY);

		// ���X�g�̐擪�Ɩ����Ɍ���ǉ�
		dataList.emplace_front(key);
		dataList.emplace_back(key);

		// �O�̍��̒l�� mod 0x100 �ŉ��Z
		int32 previousOne = 0;
		for (auto& data : dataList)
		{
			data = (data + previousOne) % MOD;
			previousOne = data;
		}

		// �����l�̔z�� -> ������
		String rtn;
		for (const auto& data : dataList)
		{
			rtn += Pad(U"{:x}"_fmt(data), { ONE_DATA_LENGTH, U'0' });
		}

		return rtn;
	}

	void RecordSet::decryption(const String& str)
	{
		// �����p�̃��X�g
		std::list<int32> dataList;
		m_isError = true;

		// ������ -> �����l�̔z��
		for (size_t i = 0; i < str.length(); i += ONE_DATA_LENGTH)
		{
			auto data = ParseIntOpt<int32>(str.substr(i, ONE_DATA_LENGTH), Arg::radix = BASE);
			if (!data)
			{
				return; // �ϊ��ł��Ȃ��Ƃ����s
			}
			dataList.emplace_back(*data);
		}

		// �O�̍��̒l�� mod 0x100 �� ���Z
		int32 previouseOne = 0;
		for (auto& data : dataList)
		{
			int32 tmp = data;
			data = (data - previouseOne + MOD) % MOD;
			previouseOne = tmp;
		}

		// �擪�E�����̌����폜
		if (*dataList.begin() != *dataList.rbegin())
		{
			return; // ������v���Ȃ��Ƃ����s
		}
		dataList.pop_front();
		dataList.pop_back();

		// �T�C�Y �� ���R�[�h�̍��v���� ����v���Ă��邩�m�F
		if (dataList.size() != totalDigit)
		{
			return; // ��v���Ȃ��Ƃ����s
		}

		// �S�Ă�0xF�Ŋ���
		for (auto& data : dataList)
		{
			if (data % MUL != 0)
			{
				return; // ����؂�Ȃ��Ƃ����s
			}
			data /= MUL;
			if (data <= 0x0 || data > BASE)
			{
				return; // [0x1,0x10]�͈̔͂ɂȂ��Ƃ����s
			}
		}

		// ���� -> 0
		// � -> 1
		for (auto& data : dataList)
		{
			data %= 2;
		}

		// ���R�[�h�Ɋi�[
		for (auto& record : m_recordMap)
		{
			record.second.setValueFromDecryption(dataList);
		}

		m_isError = false;
	}
}
