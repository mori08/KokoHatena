#pragma once

#include<Siv3D.hpp>

namespace Kokoha
{
	/// <summary>
	/// 自分で作成したピクセルシェーダの管理
	/// </summary>
	class MyPixelShader
	{
	private:

		// 自分で作成したピクセルシェーダのマップ
		std::unordered_map<String, const PixelShader> m_shaderMap;

	private:

		MyPixelShader() = default;

		/// <summary>
		/// クラス内で使用するインスタンスの取得
		/// </summary>
		/// <returns> インスタンス </returns>
		static MyPixelShader& instance()
		{
			static MyPixelShader myShader;
			return myShader;
		}

	public:

		/// <summary>
		/// ピクセルシェーダの読み取り
		/// </summary>
		static void loadPixelShader();

		/// <summary>
		/// ピクセルシェーダの取得
		/// </summary>
		/// <param name="type"> 名前 </param>
		/// <returns> ピクセルシェーダ </returns>
		static const PixelShader& get(const String& name);

	};
}
