#pragma once

#include <Siv3D.hpp>

namespace Kokoha
{
	/// <summary>
	/// EventPlayerで表示するオブジェクト
	/// </summary>
	class EventObject
	{
	protected:

		// 更新したいEventPlayerの遷移フラグ
		std::unordered_map<String, bool> m_updateJampFlagMap;

	public:

		virtual ~EventObject() = default;

		/// <summary>
		/// 命令を受け取り状態を変化させる
		/// </summary>
		/// <param name="parameter"> パラメータとなるtomlオブジェクト </param>
		virtual void receive(const TOMLValue& parameter) = 0;

		/// <summary>
		/// オブジェクトがイベント全体を待たせるかの条件
		/// </summary>
		/// <returns> true のとき待たせる , false のときイベントを進ませる </returns>
		virtual bool wait() const { return false; };

		/// <summary>
		/// 入力
		/// </summary>
		/// <param name="cursorPos"> cursorPos </param>
		virtual void input(const Vec2& cursorPos);

		/// <summary>
		/// 更新
		/// </summary>
		virtual void update() {};

		/// <summary>
		/// 描画
		/// </summary>
		virtual void draw() const {};

		/// <summary>
		/// EventPlayerの遷移フラグの更新
		/// </summary>
		/// <param name="jampFlagMap"> Event遷移フラグの連想配列 </param>
		void updateJampFlag(std::unordered_map<String, bool>& jampFlagMap);

	};
}
