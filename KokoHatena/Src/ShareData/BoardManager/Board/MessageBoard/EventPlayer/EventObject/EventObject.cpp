#include "EventObject.hpp"

namespace Kokoha
{
	void EventObject::input(const BoardArg&)
	{
	}

	void EventObject::updateJumpFlag(std::unordered_map<String, bool>& jumpFlagMap)
	{
		for (const auto& jumpFlag : m_updateJumpFlagMap)
		{
			const String& name = jumpFlag.first;
			const bool    flag = jumpFlag.second;
			jumpFlagMap[name] = flag;
		}
		m_updateJumpFlagMap.clear();
	}
}
