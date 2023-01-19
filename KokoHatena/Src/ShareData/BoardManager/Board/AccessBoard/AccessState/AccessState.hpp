#pragma once

#include "../AccessObject/AccessObject.hpp"

namespace Kokoha
{
	class AccessState
	{
	public:

		/// <summary>
		/// 更新
		/// </summary>
		/// <param name="objectMap"> guidからObjectへの連想配列 </param>
		/// <param name="typeToGuidSet"> Objectの種類からguidへの連想配列 </param>
		/// <returns> 次のAccessStateへのunique_ptr , 状態を変更しないとき none </returns>
		virtual Optional<std::shared_ptr<AccessState>> update(
			const AccessObject::GuidToObject& objectMap, 
			const AccessObject::TypeToGuidSet& typeToGuidSet) = 0;

		/// <summary>
		/// オブジェクトを更新するか
		/// </summary>
		/// <returns> trurのときは更新 , falseのときは更新しない </returns>
		virtual bool isUpdatingObject() const { return true; }

		/// <summary>
		/// 描画
		/// </summary>
		virtual void draw() const = 0;

	};
}