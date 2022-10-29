#include "TextureEventObject.hpp"

namespace Kokoha
{
	TextureEventObject::TextureEventObject(const TOMLValue&)
	{

	}

	void TextureEventObject::receive(const TOMLValue& param)
	{
		Print << param[U"text"];
	}

	void TextureEventObject::update()
	{

	}

	void TextureEventObject::draw() const
	{

	}
}