#pragma once

#include "../Terrain/Terrain.hpp"

namespace Kokoha
{
	/// <summary>
	/// AccessBoardで使用するとObject
	/// </summary>
	class AccessObject
	{
	public:

		using Ptr = std::unique_ptr<AccessObject>;

		enum class Type
		{
			PLAYER // プレイヤー
		};

	protected:

		// オブジェクトの種類
		const Type m_type;

		// GUID
		const String m_guid;

		// 位置と判定用の範囲
		Circle m_body;
		
	public:

		AccessObject(const Type& type, const Circle& body);

		AccessObject(const Type& type, const Vec2& pos);

		virtual ~AccessObject() {}

		/// <summary>
		/// guidの取得
		/// </summary>
		/// <returns> guid </returns>
		const String& guid() const
		{
			return m_guid;
		}

		/// <summary>
		/// 入力
		/// </summary>
		/// <param name="cursorPos"> カーソルの座標 </param>
		virtual void input(const Vec2& cursorPos);

		/// <summary>
		/// 更新
		/// </summary>
		/// <param name="terrain"> 地形 </param>
		virtual void update(const Terrain& terrain);

		/// <summary>
		/// 他オブジェクトの確認
		/// </summary>
		/// <param name="terrain"> 地形 </param>
		/// <param name="objectMap"> guidからオブジェクトへの連想配列 </param>
		/// <param name="typeMap"> オブジェクトの種類からguidへの連想配列 </param>
		virtual void checkOthers(const Terrain& terrain, const std::unordered_map<String, Ptr>& objectMap, const std::unordered_map<Type, std::list<String>>& typeMap);

		/// <summary>
		/// 描画
		/// </summary>
		virtual void draw() const;

		/// <summary>
		/// 光の描画
		/// </summary>
		virtual void drawLight() const;

		/// <summary>
		/// 削除条件
		/// </summary>
		/// <returns> true のとき削除 </returns>
		virtual bool isEraseAble() const;

	protected:

		/// <summary>
		/// 移動
		/// </summary>
		/// <param name="movement"> 移動量(/s) </param>
		/// <param name="terrain"> 地形 </param>
		/// <returns> 実際に移動した移動量 </returns>
		Vec2 walk(Vec2 movement, const Terrain& terrain);

		/// <summary>
		/// 目的地への移動
		/// </summary>
		/// <param name="speed"> 速さ(/s) </param>
		/// <param name="goal"> 目的地 </param>
		/// <param name="terrain"> 地形 </param>
		/// <returns> 実際に移動した移動量 </returns>
		Vec2 walkToGoal(double speed, const Vec2& goal, const Terrain& terrain);

	};
}