#pragma once
#include<Siv3D.hpp>

namespace Kokoha
{
	/// <summary>
	/// ボードの基底
	/// </summary>
	class Board
	{
	public:

		/// <summary>
		/// 種類（役割）
		/// </summary>
		enum class Role
		{
			MAIL,     // メール
			SECURITY, // セキュリティ
			ACCESS,   // アクセス（パズルアクション部分）
		};

	private:

		// 種類
		const Role m_role;

		// 名前
		const String m_name;

		// 左上の座標
		Point m_pos;

		// サイズ
		const Size m_size;

		// レンダーテクスチャー（ボード内の描画）
		const MSRenderTexture m_render;

	public:

		Board(Role role, const String& name, const Size& size);

		virtual ~Board() = default;

	public:

		/// <summary>
		/// 入力
		/// </summary>
		void input();

		/// <summary>
		/// 更新
		/// </summary>
		void update();

		/// <summary>
		/// 描画
		/// </summary>
		void draw() const;

	protected:

		/// <summary>
		/// 各ボード固有の入力処理
		/// </summary>
		virtual void inputInBoard() {};

		/// <summary>
		/// 各ボード固有の更新処理
		/// </summary>
		virtual void updateInBoard() {};

		/// <summary>
		/// 各ボード固有の描画処理
		/// </summary>
		virtual void drawInBoard() const { Circle(0, 0, 200).draw(); };

	};
}