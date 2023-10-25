#include "SliceTexture.hpp"

namespace Kokoha
{

	SliceTexture::SliceTexture(const String& textureName, const Size& sliceSize)
		: m_textureName(textureName)
		, m_sliceSize(sliceSize)
		, m_mirror(false)
		, m_animSecond(0)
		, m_animName(U"Default")
	{
		setAnimation(m_animName, Animation(PosOrder{ {0,Point::Zero()} }, false));
	}


	bool SliceTexture::update()
	{
		m_animSecond += Scene::DeltaTime();

		// 画像がループするとき
		if (m_animMap.find(m_animName)->second.loop())
		{
			if (isFinished())
			{
				m_animSecond = Fmod(m_animSecond, m_animMap.find(m_animName)->second.getTotalSecond());
			}

			return true;
		}

		return isFinished();
	}


	void SliceTexture::start(const String name)
	{
		if (!m_animMap.count(name))
		{
			throw Error(U"Faild to find [" + name + U"] record");
		}

		m_animName = name;
		m_animSecond = 0;
	}


	void SliceTexture::startAnotherAnimation(const String name)
	{
		if (name == m_animName) { return; }
		start(name);
	}


	TextureRegion SliceTexture::getTexture() const
	{
		const Point texturePos = m_animMap.find(m_animName)->second.getTexturePos(m_animSecond);

		auto texture = TextureAsset(m_textureName)(texturePos * m_sliceSize, m_sliceSize);
		if (m_mirror) { texture = texture.mirrored(); }

		return texture;
	}
}
