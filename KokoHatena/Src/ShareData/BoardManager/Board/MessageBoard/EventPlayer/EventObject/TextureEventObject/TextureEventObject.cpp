#include "TextureEventObject.hpp"
#include "../../../../../../../Config/Config.hpp"


namespace Kokoha
{
	TextureEventObject::TextureEventObject(const TOMLValue& param)
		: m_texture(
			Config::get<SliceTexture>(U"TextureEventObject." + param[U"objectKey"].getString())
		)
		, m_pos(0, tomlToPos(param[U"pos"]), tomlToPos(param[U"pos"]))
		, m_isHidden(false)
		, m_mirror(false)
	{
		
	}

	void TextureEventObject::receive(const TOMLValue& param)
	{
		if (auto anim = param[U"anim"].getOpt<String>())
		{
			m_texture.start(anim.value());
		}
		
		auto posT = param[U"pos.t"].getOpt<double>();
		auto posX = param[U"pos.x"].getOpt<int32>();
		auto posY = param[U"pos.y"].getOpt<int32>();
		if (posT && posX && posY)
		{
			m_pos = Linearly<Vec2>(
				posT.value(),
				m_pos.getGoal(),
				Point(posX.value(), posY.value())
			);
		}

		auto moveT = param[U"move.t"].getOpt<double>();
		auto moveX = param[U"move.x"].getOpt<int32>();
		auto moveY = param[U"move.y"].getOpt<int32>();
		if (moveT && moveX && moveY)
		{
			m_pos = Linearly<Vec2>(
				moveT.value(),
				m_pos.getGoal(),
				m_pos.getGoal() + Point(moveX.value(), moveY.value())
			);
		}

		if (auto hide = param[U"hide"].getOpt<bool>())
		{
			m_isHidden = hide.value();
		}

		if (auto mirror = param[U"mirror"].getOpt<bool>())
		{
			m_texture.mirror(mirror.value());
		}

		m_isWaiting = true;
	}

	bool TextureEventObject::wait() const
	{
		return m_isWaiting;
	}

	void TextureEventObject::update()
	{
		const bool posWait = m_pos.update();
		const bool texWait = m_texture.update();
		
		if (posWait && texWait)
		{
			m_isWaiting = false;
		}
	}

	void TextureEventObject::draw() const
	{
		if (m_isHidden) { return; }

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