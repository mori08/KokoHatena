#pragma once

#include "../AccessObject/AccessObject.hpp"
#include "../../BoardConst.hpp"

namespace Kokoha
{
	class AccessState
	{
	public:

		virtual ~AccessState() {};

	public:

		/// <summary>
		/// 入力
		/// </summary>
		/// <param name="board"> Boardの情報 </param>
		virtual void input(const BoardArg& board);

		/// <summary>
		/// 更新
		/// </summary>
		/// <param name="objectMap"> guidからObjectへの連想配列 </param>
		/// <param name="typeToGuidSet"> Objectの種類からguidへの連想配列 </param>
		/// <param name="typeToGuidSet"> AccessBoardのBoardRequest </param>
		/// <returns> 次のAccessStateへのunique_ptr , 状態を変更しないとき none </returns>
		virtual Optional<std::shared_ptr<AccessState>> update(
			AccessObject::GuidToObject& objectMap, 
			AccessObject::TypeToGuidSet& typeToGuidSet,
			BoardRequest& boradRequest) = 0;

		/// <summary>
		/// オブジェクトを更新するか
		/// </summary>
		/// <returns> trurのときは更新 , falseのときは更新しない </returns>
		virtual bool isUpdatingObject() const = 0;

		/// <summary>
		/// オブジェクトを初期化するか
		/// </summary>
		/// <returns> trurのときは初期化 , falseのときは初期化しない </returns>
		virtual bool isInitializingObject()
		{
			return false;
		}

		/// <summary>
		/// 描画
		/// </summary>
		virtual void draw() const = 0;

	};
}
