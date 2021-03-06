#pragma once


#include "../SecurityState.hpp"


namespace Kokoha
{
	/// <summary>
	/// SecurityWaitStateクラス
	/// 待ち状態
	/// </summary>
	class SecurityWaitState : public SecurityState
	{
	public:

		void input(Optional<Vec2> mouseUpPos) override;

		void update(const Vec2& cursorPosInBoard) override;

		void draw() const override;

	};
}