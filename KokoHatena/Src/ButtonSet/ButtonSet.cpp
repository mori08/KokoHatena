#include "ButtonSet.hpp"


namespace Kokoha
{
	void ButtonSet::registerButton(const String& name, const Rect& region)
	{
		registerButton(Button(name, region));
	}

	void ButtonSet::registerButton(const Button& button)
	{
		if (m_buttonMap.empty())
		{
			m_selectedButtonName = button.getName();
		}

		m_buttonMap.try_emplace(button.getName(), std::move(Button(button)));
	}

	void ButtonSet::setSelectedButton(const String& name)
	{
		if (!m_buttonMap.count(name))
		{
			throw Error(U"Faild to find [" + name + U"] button");
		}

		m_selectedButtonName = name;
	}

	void ButtonSet::setOnClickFunc(const String& name, std::function<void()> onClickFunc)
	{
		if (!m_buttonMap.count(name))
		{
			throw Error(U"Faild to find [" + name + U"] button");
		}

		m_buttonMap.find(name)->second.setOnClickFunc(onClickFunc);
	}

	const Button& ButtonSet::getSelectedButton() const
	{
		if (!m_buttonMap.count(m_selectedButtonName))
		{
			throw Error(U"Faild to find [" + m_selectedButtonName + U"] button");
		}

		return m_buttonMap.find(m_selectedButtonName)->second;
	}

	void ButtonSet::eraseButton(const String& name)
	{
		if (!m_buttonMap.count(name))
		{
			throw Error(U"Faild to find [" + name + U"] button");
		}

		m_buttonMap.erase(name);
	}

	void ButtonSet::clearButtonList()
	{
		m_buttonMap.clear();
	}

	bool ButtonSet::update(const Point& basePos)
	{
		for (const auto& itr : m_buttonMap)
		{
			if (!itr.second.getRegion().movedBy(basePos).mouseOver()) { continue; }

			bool rtn = (m_selectedButtonName != itr.first);
			m_selectedButtonName = itr.first;

			if (MouseL.up())
			{
				itr.second.onClick();
			}

			return rtn;
		}

		return false;
	}
}
