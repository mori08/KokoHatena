#pragma once

#include "Animation/Animation.hpp"

namespace Kokoha
{
	/// <summary>
	/// SliceTextureクラス
	/// 1枚の画像を複数の画像に分け,
	/// 切り替えなどを行えるようにする.
	/// </summary>
	class SliceTexture
	{
	private:

		// 画像の名前
		const String m_textureName;

		// 画像を切り分ける大きさ
		const Size m_sliceSize;

		// true のとき左右反転して描画
		bool m_mirror;

		// (1つの)アニメーションを実行している時間
		double m_animSecond;

		// 現在のAnimationの名前
		String m_animName;

		// Animationを管理するマップ
		std::unordered_map<String, Animation> m_animMap;

	public:

		/// <summary>
		/// 画像の切り分け
		/// </summary>
		/// <param name="textureName"> 画像の名前             </param>
		/// <param name="sliceSize">   画像を切り分ける大きさ </param>
		/// <param name="pos">         画像の初期番号         </param>
		SliceTexture(const String& textureName, const Size& sliceSize);

		/// <summary>
		/// アニメーションの設定
		/// </summary>
		/// <param name="anim"> アニメーション </param>
		void setAnimation(const String& name, const Animation& anim)
		{
			m_animMap.try_emplace(name, anim);
		}

		/// <summary>
		/// 画像の変更
		/// </summary>
		/// <returns>
		/// 画像の切り替えが終了したとき true , そうでないとき false
		/// ループしているときは true を常に返すので注意
		/// </returns>
		bool update();

		/// <summary>
		/// 現在実行中のアニメーションが終了しているか示す
		/// </summary>
		/// <returns> 終了しているなら true , 実行中なら false </returns>
		bool isFinished() const
		{
			return m_animSecond > m_animMap.find(m_animName)->second.getTotalSecond();
		}

		/// <summary>
		/// 画像の反転
		/// </summary>
		void mirror()
		{
			m_mirror = !m_mirror;
		}

		/// <summary>
		/// 画像の反転
		/// </summary>
		/// <param name="mirror"> trueのとき反転, falseのとき反転を解除 </param>
		void mirror(bool mirror)
		{
			m_mirror = mirror;
		}

		/// <summary>
		/// アニメーションの開始
		/// </summary>
		/// <param name="name"> アニメーションの名前 </param>
		void start(const String name);

		/// <summary>
		/// 別アニメーションの開始
		/// 現在実行中のものと同じ名前が指定されたら何もしない
		/// </summary>
		/// <param name="name"> アニメーション名 </param>
		void startAnotherAnimation(const String name);

		/// <summary>
		/// 画像の変更
		/// </summary>
		TextureRegion getTexture() const;

		/// <summary>
		/// 画像を切り分ける大きさの取得
		/// </summary>
		const Size& getSliceSize() const
		{
			return m_sliceSize;
		}

	};
}