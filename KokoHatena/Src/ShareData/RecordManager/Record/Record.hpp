#pragma once
#include<Siv3D.hpp>

namespace Kokoha
{
	/// <summary>
	/// フラグや数値の管理
	/// 何bitに対応するか指定
	/// </summary>
	class Record
	{
	private:

		// 桁数
		const int32 m_digit;

		// 最大値
		const int32 m_maxValue;

		// 初期値
		const int32 m_defaultValue;

		// 値
		uint32 m_value;

	public:

		/// <summary>
		/// レコードを構成する要素
		/// </summary>
		/// <param name="digit">        桁数   </param>
		/// <param name="defaultValue"> 初期値 </param>
		Record(int32 digit, int32 defaultValue);

		/// <summary>
		/// 初期化
		/// </summary>
		void init()
		{
			m_value = m_defaultValue;
		}

		/// <summary>
		/// 値の設定
		/// </summary>
		/// <param name="value"> 変更したい値 </param>
		void set(int32 value)
		{
			m_value = Clamp(value, 0, m_maxValue);
		}

		/// <summary>
		/// 値の取得
		/// </summary>
		/// <returns>
		/// 管理している値
		/// </returns>
		int32 get() const
		{
			return m_value;
		}

		/// <summary>
		/// 暗号化用のリストにこのレコードを追加
		/// </summary>
		/// <param name="dataList"> 暗号化用のリスト </param>
		void addRecordToEncryptionList(std::list<int32>& dataList) const;

		/// <summary>
		/// 復号可用のリストから値を設定
		/// </summary>
		/// <param name="dataList"> 復号化用のリスト </param>
		void setValueFromDecryption(std::list<int32>& dataList);

	};
}