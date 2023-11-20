#include "BoardConst.hpp"
#include "../../../Config/Config.hpp"

Vec2 Kokoha::BoardArg::cursorPos() const
{
	static const int32 CONTROL_FRAME_HEIGHT = Kokoha::Config::get<int32>(U"Board.controlFrameHeight");
	return Cursor::PosF() - m_boardRect.pos - Vec2::Down(CONTROL_FRAME_HEIGHT);
}
