#include "TutorialAccessState.hpp"
#include "../../../../../../Config/Config.hpp"
#include "../../../../../../MyLibrary/MyLibrary.hpp"

namespace Kokoha
{
	TutorialAccessState::TutorialAccessState()
		: m_wordsCount(0)
		, m_textId(0)
		, m_textPos(Scene::Rect().center())
	{
	}

	Optional<std::shared_ptr<AccessState>> TutorialAccessState::update(
		AccessObject::GuidToObject& objectMap,
		AccessObject::TypeToGuidSet& typeToGuidSet,
		BoardRequest& boardRequest
	)
	{
		static const double WORDS_PER_SECOND = Config::get<double>(U"TutorialAccessState.wordsPerTime");
		static const double NEXT_WORD_COUNT = Config::get<double>(U"TutorialAccessState.nextWordCount");
		static const Array<String> TEXT_LIST = Config::getArray<String>(U"TutorialAccessState.textList");
		static const Vec2 BOARD_SIZE = Config::get<Vec2>(U"AccessBoard.size");

		m_wordsCount += WORDS_PER_SECOND * Scene::DeltaTime();
		if (m_wordsCount > NEXT_WORD_COUNT)
		{
			m_wordsCount = 0;
			m_textId = (m_textId + 1) % TEXT_LIST.size();
			m_textPos = RandomVec2(RectF(BOARD_SIZE));
		}

		return PlayingAccessState::update(objectMap, typeToGuidSet, boardRequest);
	}

	void TutorialAccessState::draw() const
	{
		static const Array<String> TEXT_LIST = Config::getArray<String>(U"TutorialAccessState.textList");

		FontAsset(U"20")(TEXT_LIST[m_textId].substr(0, (size_t)m_wordsCount)).drawAt(m_textPos, MyWhite);
	}
}
