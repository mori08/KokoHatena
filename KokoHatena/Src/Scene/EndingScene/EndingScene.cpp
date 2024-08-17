#include "EndingScene.hpp"
#include "../../Config/Config.hpp"
#include "../../MyLibrary/MyLibrary.hpp"

namespace Kokoha
{
	EndingScene::EndingScene(const InitData& init)
		: IScene(init)
		, m_textId(0)
		, m_wordsCount(0)
		, m_radiusTexture(Config::get<SliceTexture>(U"TextureEventObject.Researcher"))
	{
		m_radiusTexture.start(U"wait");
	}

	void EndingScene::update()
	{
		static const double WORDS_PER_TIME = Config::get<double>(U"LastAccessState.wordsPerTime");
		m_wordsCount += WORDS_PER_TIME * Scene::DeltaTime();

		m_radiusTexture.update();

		if (textList()[m_textId].length() < (size_t)m_wordsCount && MouseL.down())
		{
			if (m_textId < textList().size() - 1)
			{
				++m_textId;
				m_wordsCount = 0;
			}
			else
			{
				changeScene(SceneName::TITLE);
			}
		}
	}

	void EndingScene::draw() const
	{
		Scene::Rect().draw(MyWhite);

		FontAsset(U"18")(textList()[m_textId].substr(0, (size_t)m_wordsCount))
			.drawAt(Scene::CenterF(), MyBlack);

		m_radiusTexture.getTexture().drawAt(Scene::CenterF() + Vec2::Down(150));
	}

	const Array<String>& EndingScene::textList() const
	{
		static const Array<String> rtn = Config::getArray<String>(U"EndingScene.textList");
		return rtn;
	}
}
