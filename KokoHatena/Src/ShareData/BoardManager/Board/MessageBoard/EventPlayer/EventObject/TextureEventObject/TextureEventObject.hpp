#pragma once

#include "../EventObject.hpp"
#include "../../../../../../../MyLibrary/Linearly/Linearly.hpp"
#include "../../../../../../../MyLibrary/SliceTexture/SliceTexture.hpp"

namespace Kokoha
{
	/// <summary>
	/// 画像を表示するEventPlayer用オブジェクト
	/// </summary>
	class TextureEventObject : public EventObject
	{
	private:

		/// <summary>
		/// 表示する画像の情報
		/// </summary>
		class Slice
		{
		public:
			double time;   // 画像を表示する時間
			int32  id;     // 表示する画像の番号（左から何番目か）
			bool   mirror; // true なら 反転 , false なら 反転
			Slice(double t, int32 i, bool m)
				: time(t), id(i), mirror(m)
			{
			}
		};

	private:

		// 表示する座標
		Linearly<Vec2> m_pos;

		// 表示する画像データ
		SliceTexture m_texture;

	public:

		TextureEventObject(const TOMLValue& param);

		void receive(const TOMLValue& param) override;

		void update() override;

		void draw() const override;

	private:

		/// <summary>
		/// TOMLValueをPointに変更する
		/// </summary>
		/// <param name="toml"> 設定ファイルデータ </param>
		/// <returns> 座標 </returns>
		static Point tomlToPos(const TOMLValue& toml);

	};
}
