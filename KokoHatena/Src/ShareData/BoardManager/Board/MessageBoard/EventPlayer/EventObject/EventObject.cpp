#include "EventObject.hpp"

namespace Kokoha
{
	void EventObject::input(const Vec2&)
	{
	}

	void EventObject::updateJampFlag(std::unordered_map<String, bool>& jampFlagMap)
	{
		for (const auto& jampFlag : m_updateJampFlagMap)
		{
			const String& name = jampFlag.first;
			const bool    flag = jampFlag.second;
			jampFlagMap[name] = flag;
		}
		m_updateJampFlagMap.clear();
	}
}
