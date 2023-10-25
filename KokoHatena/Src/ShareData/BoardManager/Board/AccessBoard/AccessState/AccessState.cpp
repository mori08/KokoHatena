#include "AccessState.hpp"
#include "../../../../../Config/Config.hpp"

namespace Kokoha
{
	const Rect& AccessState::boardRect()
	{
		static const Rect rtn = Rect(Point::Zero(), Config::get<Size>(U"AccessBoard.size"));
		return rtn;
	}
}
