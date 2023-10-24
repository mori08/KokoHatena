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
			const String m_text;

			// 表示する文字列（サイズにあわせて改行）
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
			/// 表示する文字列の取得
			/// </summary> 
			const String& getText() const
			{
				return m_text;
			}

			/// <summary>
			/// 投稿を表示するサイズの取得
			/// </summary>
			/// <returns> 投稿を表示するサイズ </returns>
			const Size& getSize() const
			{
				return m_textRectSize;
			}

			/// <summary>
			/// 投稿を表示する範囲の取得
			/// </summary>
			/// <returns> 投稿を表示する範囲 </returns>
			Rect getRect() const;

			/// <summary>
			/// 表示するy座標を設定する
			/// </summary>
			/// <param name="y"> y座標 </param>
			void setPosY(int32 y)
			{
				m_pos.y = y;
			}

			/// <summary>
			/// 描画
			/// </summary>
			/// <param name="rectColor"> 枠を描画する色 </param>
			/// <param name="textColor"> 文字を描画する色 </param>
			void draw(const ColorF& rectColor, const ColorF& textColor) const;

		private:

			/// <summary>
			/// 横幅を抑えるために文字列を分割
			/// </summary>
			/// <param name="subText"> 分割したい文字列 </param>
			void splitTextFromWidth(const String& subText);

		};


		/// <summary>
		/// 投稿する時の選択肢
		/// </summary>
		class Select
		{
		private:

			// 選択肢
			Array<Post> m_selectAry;

			// jump用のフラグ名
			HashTable<String, String> m_flagNameMap;

			// 表示する座標
			Point m_pos;

			// 文字のalpha値
			double m_textAlpha;

		public:

			Select(const TOMLValue& selectTomlAry);

			/// <summary>
			/// y座標の設定
			/// </summary>
			/// <param name="y"> y座標 </param>
			void setPosY(int32 y);

			/// <summary>
			/// いずれかの選択肢をクリックしたか
			/// </summary>
			/// <param name="cursorPos"> マウスカーソルの座標 </param>
			Optional<String> input(const Vec2& cusrorPos);

			void update();

			void draw() const;

		};

	private:

		// 画面に標示する投稿のリスト
		std::list<Post> m_postList;

		// 選択肢
		Optional<Select> m_select;

		// 待ち時間
		double m_waitSecond;

	public:

		MessageEventObject(const TOMLValue& param);

		void receive(const TOMLValue& param) override;

		bool wait() const override;

		void input(const Vec2& cursorPos) override;

		void update() override;

		void draw() const override;

	private:

		/// <summary>
		/// PostやSelectのy座標を更新
		/// </summary>
		void updatePostPos();

	};
}
