#include "BoardConst.hpp"
#include "../../../Config/Config.hpp"

namespace Kokoha
{
	void BoardArg::setPos(const Vec2& pos)
	{
		static const int32 CONTROL_FRAME_HEIGHT = Kokoha::Config::get<int32>(U"Board.controlFrameHeight");
		m_boardRect.pos = pos + Vec2::Down(CONTROL_FRAME_HEIGHT);
	}

	Vec2 BoardArg::cursorPos() const
	{
		return Cursor::PosF() - m_boardRect.pos;
	}
}
