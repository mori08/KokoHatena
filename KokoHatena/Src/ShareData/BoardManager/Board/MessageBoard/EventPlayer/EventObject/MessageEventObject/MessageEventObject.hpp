#pragma once

#include "../EventObject.hpp"

namespace Kokoha
{
	/// <summary>
	/// メッセージアプリ風のテキストを表示するEventPlayerオブジェクト
	/// </summary>
	class MessageEventObject : public EventObject
	{
	private:

		/// <summary>
		/// 表示する投稿
		/// </summary>
		class Post
		{
		private:

			// 話し手 true なら自分 , falseなら相手
			const bool m_isMine;

			// 表示する文字列
			Array<String> m_rowList;

			// テキスト表示に必要なサイズ
			Size m_textRectSize;

			// 表示する座標
			Point m_pos;

		public:

			/// <param name="isMine"> 話し手 (true なら自分 , falseなら相手) </param>
			/// <param name="text"> １行で表示する文字列のリスト </param>
			Post(bool isMine, const String& text);

			/// <summary>
			/// 画像を表示するサイズの取得
			/// </summary>
			/// <returns> 画像を表示するサイズ </returns>
			const Size& getSize() const
			{
				return m_textRectSize;
			}

			/// <summary>
			/// 描画
			/// </summary>
			/// <param name="posY"> 表示するy座標 </param>
			void draw(int32 posY) const;

		private:

			/// <summary>
			/// 横幅を抑えるために文字列を分割
			/// </summary>
			/// <param name="subText"> 分割したい文字列 </param>
			void splitTextFromWidth(const String& subText);

		};

	private:

		// 画面に標示する投稿のリスト
		std::list<Post> m_postList;

		// 投稿作成用の引数
		Optional<std::pair<bool, String>> m_postArg;

		// 待ち時間
		double m_waitSecond;

	public:

		MessageEventObject(const TOMLValue& param);

		void receive(const TOMLValue& param) override;

		bool wait() const override;

		void update() override;

		void draw() const override;

	};
}
