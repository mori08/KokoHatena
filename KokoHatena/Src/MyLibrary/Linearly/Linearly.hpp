#pragma once

#include <Siv3D.hpp>

namespace Kokoha
{
	/// <summary>
	/// 線型的に値を変更
	/// 主にdoubleやVec2,Vec3などの小数値で扱う
	/// </summary>
	/// <typeparam name="Type"> 変更する値の型 </typeparam>
	template<typename Type>
	class Linearly
	{
	private:

		// 何秒で値を変更するか (DeltaTimeを下回ると1フレームでmRateを1にする)
		double m_changeSecond;

		// 端点 { 始点, 終点 }
		std::pair<Type, Type> m_endPoint;

		// 内分比 [0,1]
		double m_rate;

	public:

		/// <summary>
		/// 線形補完
		/// </summary>
		/// <param name="changeSecond"> 何秒で値を変更するか </param>
		/// <param name="start"       > 始点                 </param>
		/// <param name="goal"        > 終点                 </param>
		Linearly(double changeSecond, const Type& start, const Type& goal)
			: m_changeSecond(changeSecond)
			, m_endPoint({ start,goal })
			, m_rate(0)
		{
		}

		/// <summary>
		/// 線形補完
		/// </summary>
		/// <param name="changeSecond"> 何秒で値を変更するか </param>
		/// <param name="goal"        > 終点                 </param>
		Linearly(double changeSecond, Type goal)
			: m_changeSecond(changeSecond)
			, m_endPoint({ Type(),goal })
			, m_rate(0)
		{
		}

		/// <summary>
		/// 始点に戻す
		/// </summary>
		void restart()
		{
			m_rate = 0;
		}

		/// <summary>
		/// 終点にとばす
		/// </summary>
		void toGoal()
		{
			m_rate = 1;
		}

		/// <summary>
		/// 更新
		/// </summary>
		/// <returns>
		/// 内分比が 1 を超えたら true, そうでないとき false
		/// </returns>
		bool update()
		{
			const double deltaTime = Scene::DeltaTime();

			if (deltaTime > m_changeSecond) // mChangeSecondが0以下のときの対策
			{
				m_rate = 1;
				return true;
			}

			m_rate += deltaTime / m_changeSecond;

			if (m_rate > 1)
			{
				m_rate = 1;
				return true;
			}

			return false;
		}

		/// <summary>
		/// 値の取得
		/// </summary>
		Type getValue() const
		{
			return Type(m_endPoint.first + m_rate * (m_endPoint.second - m_endPoint.first));
		}

		/// <summary>
		/// 終点の取得
		/// </summary>
		Type getGoal() const
		{
			return m_endPoint.second;
		}
	};
}