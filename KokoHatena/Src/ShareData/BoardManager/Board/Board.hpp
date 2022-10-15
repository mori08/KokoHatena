#pragma once
#include"../../../MyLibrary/SliceTexture/SliceTexture.hpp"
#include"../../../Scene/SceneName.hpp"

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
			MESSAGE,  // メッセージ
			SECURITY, // セキュリティ
			ACCESS,   // アクセス（パズルアクション部分）
		};

		/// <summary>
		/// 状態
		/// </summary>
		enum class State
		{
			IS_DISPLAYED, // 表示中
			IS_HIDING,    // 非表示
			NONE,         // 利用不可
		};

		/// <summary>
		/// 外部へ送信するデータ
		/// </summary>
		class Request
		{
		public:

			// 他ボードへの命令
			std::list<std::pair<Role, String>> toBoard;

			// Recordへの書き込み
			std::unordered_map<String, int32> toRecord;

			// Scene遷移
			Optional<SceneName> toScene = none;
		};

	private:

		// 種類
		const Role m_role;

		// 状態
		State m_state;

		// 名前
		const String m_name;

		// サイズ
		const Size m_size;

		// 左上の座標
		Point m_pos;

		// レンダーテクスチャー（ボード内の描画）
		const MSRenderTexture m_render;

		// 座標移動時の基準座標 (noneのとき移動しない)
		Optional<Point> m_optMovePos;

		// アイコン画像の名前
		String m_iconTextureName;

		// アイコンの表示順(-1だと非表示)
		const int32 m_iconOrder;

	public:

		/// <param name="role"> 種類(役割) </param>
		/// <param name="configName"> configファイルでの名前 </param>
		/// <param name="state"> 初期状態 </param>
		Board(const Role& role, const String& configName, const State& state);

		virtual ~Board() = default;

	public:

		/// <summary>
		/// ボードの種類の取得
		/// </summary>
		/// <returns> ボードの種類 </returns>
		const Role& role() const
		{
			return m_role;
		}

		/// <summary>
		/// ボードの状態の取得
		/// </summary>
		/// <returns> ボードの状態 </returns>
		const State& state() const
		{
			return m_state;
		}

		/// <summary>
		/// ボードを表示する状態へ変更
		/// </summary>
		void display()
		{
			m_state = State::IS_DISPLAYED;
		}

		/// <summary>
		/// ボードを非表示にする状態へ変更
		/// </summary>
		void hide()
		{
			m_state = State::IS_HIDING;
		}

		/// <summary>
		/// アイコンがクリックされたか
		/// </summary>
		/// <returns> 
		/// 以下の条件を全て満たすとき true , それ以外の場合false
		/// * アイコンがクリックされた
		/// * m_stateがNONEでない
		/// * m_iconOrderが-1でない
		/// </returns>
		bool onIconClicked() const;

		/// <summary>
		/// ボードがクリックされたか
		/// </summary>
		/// <returns>
		/// m_stateがDISPLAYED かつ ボードがクリックされたとき true , そうでないとき false
		/// </returns>
		bool mouseLeftDown() const;

		/// <summary>
		/// アイコンの描画
		/// </summary>
		void drawIcon() const;

		/// <summary>
		/// 入力
		/// </summary>
		/// <returns> true のときボードを閉じる </returns>
		bool input();

		/// <summary>
		/// 更新
		/// </summary>
		/// <param name="request"> ボード外部への命令 </param>
		void update(Request& request);

		/// <summary>
		/// 描画
		/// </summary>
		void draw() const;

		/// <summary>
		/// 他ボードからデータの受信
		/// </summary>
		/// <param name="requestText"> データとなる文字列 </param>
		virtual void receiveRequest(const String& requestText) = 0;

	protected:

		/// <summary>
		/// 各ボード固有の入力処理
		/// </summary>
		virtual void inputInBoard() = 0;

		/// <summary>
		/// 各ボード固有の更新処理
		/// </summary>
		virtual void updateInBoard(Request& request) = 0;

		/// <summary>
		/// 各ボード固有の描画処理
		/// </summary>
		virtual void drawInBoard() const = 0;

	protected:

		/// <summary>
		/// ボードのサイズを取得
		/// </summary>
		/// <returns> サイズ </returns>
		const Size& size() const
		{
			return m_size;
		}

		/// <summary>
		/// ボード内のマウス座標の取得
		/// </summary>
		/// <returns> ボード内のマウス座標 </returns>
		Point cursorPosInBoard() const
		{
			return cursorPosFInBoard().asPoint();
		}

		/// <summary>
		/// ボード内のマウス座標の取得
		/// </summary>
		/// <returns> ボード内のマウス座標 </returns>
		Vec2 cursorPosFInBoard() const;

	private:

		/// <summary>
		/// カーソルで座標を移動する
		/// </summary>
		void movePosByCursor();

		/// <summary>
		/// アイコンの範囲の取得
		/// </summary>
		/// <returns> アイコンの範囲の長方形 </returns>
		const Rect getIconRect() const;

		/// <summary>
		/// 非表示ボタンの範囲を示す長方形の取得
		/// </summary>
		/// <returns> 非表示ボタンの範囲 </returns>
		const Rect hideButtonRect() const;

	};
}