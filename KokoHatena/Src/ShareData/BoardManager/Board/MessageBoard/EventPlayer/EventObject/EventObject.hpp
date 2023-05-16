#pragma once

#include <Siv3D.hpp>

namespace Kokoha
{
	/// <summary>
	/// EventPlayerで表示するオブジェクト
	/// </summary>
	class EventObject
	{
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
		virtual void input() {};

		/// <summary>
		/// 更新
		/// </summary>
		virtual void update() {};

		/// <summary>
		/// 描画
		/// </summary>
		virtual void draw() const {};

	};
}