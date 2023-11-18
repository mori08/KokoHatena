#pragma once

#include "../Terrain/Terrain.hpp"
#include "../../BoardConst.hpp"
#include "AccessLight/AccessLight.hpp"

namespace Kokoha
{
	/// <summary>
	/// AccessBoardで使用するとObject
	/// </summary>
	class AccessObject
	{
	public:

		enum class Type
		{
			PLAYER, // プレイヤー
			ENEMY,  // 敵
			MINION, // 手先
			GOAL    // ゴール
		};

		using Ptr = std::shared_ptr<AccessObject>;

		using GuidToObject = std::unordered_map<String, Ptr>;

		using TypeToGuidSet = std::unordered_map<Type, std::unordered_set<String>>;

		/// <summary>
		/// Typeが合う先頭オブジェクトのGuidを取得
		/// </summary>
		/// <param name="type"> オブジェクトの種類 </param>
		/// <param name="typeToGuidSet"> typeからguid集合への連想配列 </param>
		/// <returns> 存在するときは guid , 集合が空のときは none </returns>
		static Optional<String> getFrontGuid(Type type, const TypeToGuidSet& typeToGuidSet);

	private:

		// オブジェクトの種類
		const Type m_type;

		// GUID
		const String m_guid;

		// true のとき 削除する
		bool m_isErase;

		// 作成するオブジェクトのリスト
		std::list<AccessObject::Ptr> m_makeObjectList;

		// 位置と判定用の範囲
		Circle m_body;

		// 光
		AccessLight m_light;
		
	public:

		AccessObject(const Type& type, const Circle& body);

		AccessObject(const Type& type, const Vec2& pos);

		virtual ~AccessObject() {}

		static void setMakingObject(Ptr ptr, GuidToObject& objectMap, TypeToGuidSet& typeToGuidSet);

	public:

		/// <summary>
		/// typeの取得
		/// </summary>
		/// <returns> type </returns>
		const Type& type() const
		{
			return m_type;
		}

		/// <summary>
		/// guidの取得
		/// </summary>
		/// <returns> guid </returns>
		const String& guid() const
		{
			return m_guid;
		}

		/// <summary>
		/// bodyの取得
		/// </summary>
		/// <returns> body </returns>
		const Circle& body() const
		{
			return m_body;
		}

		/// <summary>
		/// 入力
		/// </summary>
		/// <param name="board"> Boardの情報 </param>
		virtual void input(const BoardArg& board);

		/// <summary>
		/// 更新
		/// </summary>
		/// <param name="terrain"> 地形 </param>
		virtual void update(const Terrain& terrain);

		/// <summary>
		/// 他オブジェクトの確認
		/// </summary>
		/// <param name="terrain"> 地形 </param>
		/// <param name="guidToObject"> guidからオブジェクトへの連想配列 </param>
		/// <param name="typeToGuidSet"> オブジェクトの種類からguidへの連想配列 </param>
		virtual void checkOthers(const Terrain& terrain, const GuidToObject& guidToObject, const TypeToGuidSet& typeToGuidSet);

		/// <summary>
		/// 追加オブジェクトをオブジェクトリストに追加
		/// </summary>
		/// <param name="makeObjectList"> オブジェクトの作成リスト </param>
		virtual void addObjectList(std::list<AccessObject::Ptr>& makeObjectList);

		/// <summary>
		/// 削除条件
		/// </summary>
		/// <returns> true のとき削除 </returns>
		virtual bool isEraseAble() const;

		/// <summary>
		/// 描画
		/// </summary>
		virtual void draw() const;

		/// <summary>
		/// 光の描画
		/// </summary>
		virtual void drawLight() const;

		/// <summary>
		/// 光
		/// </summary>
		/// <returns> 光の参照 </returns>
		AccessLight& light()
		{
			return m_light;
		}

	protected:

		/// <summary>
		/// このオブジェクトを削除する
		/// </summary>
		void erase()
		{
			m_isErase = true;
		}

		/// <summary>
		/// 他のオブジェクトを作成する
		/// </summary>
		/// <param name="objectPtr"> 作成するオブジェクトのunique_ptr </param>
		void makeObject(AccessObject::Ptr&& object)
		{
			m_makeObjectList.emplace_back(std::move(object));
		}

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
