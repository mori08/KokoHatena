#include"Record.hpp"

namespace
{
	// åÖÇÃç≈ëÂíl
	constexpr int32 MAX_DIGIT = 30;
}

namespace Kokoha
{
	Record::Record(int32 digit, int32 defaultValue)
		: m_digit(Clamp(digit, 1, MAX_DIGIT))
		, m_maxValue((1 << m_digit) - 1)
		, m_defaultValue(Clamp(defaultValue, 0, m_maxValue))
		, m_value(m_defaultValue)
	{
	}

	void Record::addRecordToEncryptionList(std::list<int32>& dataList) const
	{
		for (int32 i = 0; i < m_digit; ++i)
		{
			// iåÖñ⁄Çí«â¡
			dataList.emplace_back((m_value >> i) & 1);
		}
	}

	void Record::setValueFromDecryption(std::list<int32>& dataList)
	{
		m_value = 0;

		for (int32 i = 0; i < m_digit; ++i)
		{
			if (dataList.empty()) { return; }

			// iåÖñ⁄Ç…í«â¡
			m_value |= dataList.front() << i;
			dataList.pop_front();
		}
	}
}