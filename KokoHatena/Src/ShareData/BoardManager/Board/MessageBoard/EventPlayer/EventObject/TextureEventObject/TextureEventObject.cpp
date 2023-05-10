#include "TextureEventObject.hpp"
#include "../../../../../../../Config/Config.hpp"


namespace Kokoha
{
	TextureEventObject::TextureEventObject(const TOMLValue& param)
		: m_texture(
			Config::get<SliceTexture>(U"TextureEventObject." + param[U"objectKey"].getString())
		)
		, m_pos(0, tomlToPos(param[U"pos"]), tomlToPos(param[U"pos"]))
	{
		
	}

	void TextureEventObject::receive(const TOMLValue& param)
	{
		
	}

	void TextureEventObject::update()
	{
		m_pos.update();
		m_texture.update();
	}

	void TextureEventObject::draw() const
	{
		m_texture.getTexture().draw(m_pos.getValue());
	}

	Point TextureEventObject::tomlToPos(const TOMLValue& toml)
	{
		return Point(
			toml[U"x"].get<int32>(),
			toml[U"y"].get<int32>()
		);
	}
}