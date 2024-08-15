#include "LastAccessState.hpp"
#include "../StartingAccessState/StartingAccessState.hpp"
#include "../../../../../../Config/Config.hpp"

namespace Kokoha
{
	LastAccessState::LastAccessState()
		: m_wordsCount(0)
		, m_textId(0)
	{
	}

	void LastAccessState::input(const BoardArg& board)
	{
		if (textList()[m_textId].length() < (size_t)m_wordsCount && board.rect().leftClicked())
		{
			++m_textId;
			m_wordsCount = 0;
		}
	}

	Optional<std::shared_ptr<AccessState>> LastAccessState::update(
		AccessObject::GuidToObject& objectMap,
		AccessObject::TypeToGuidSet& typeToGuidSet,
		BoardRequest& boradRequest
	)
	{
		static const double WORDS_PER_SECOND
			= Config::get<double>(U"LastAccessState.wordsPerTime");

		m_wordsCount += WORDS_PER_SECOND * Scene::DeltaTime();

		if (m_textId >= textList().size())
		{
			return std::make_shared<StartingAccessState>(U"last");
		}
		
		return none;
	}

	void LastAccessState::draw()const
	{
		static const Vec2 TEXT_POS
			= Config::get<Vec2>(U"LastAccessState.textPos");

		static const Vec2 KIOKU_POS
			= Config::get<Vec2>(U"LastAccessState.kiokuPos");

		FontAsset(U"18")(textList()[m_textId].substr(0, (size_t)m_wordsCount))
			.drawAt(TEXT_POS);

		TextureAsset(U"Kioku").drawAt(KIOKU_POS);
	}

	const Array<String>& LastAccessState::textList()
	{
		static const Array<String> TEXT_LIST
			= Config::getArray<String>(U"LastAccessState.textList");
		return TEXT_LIST;
	}
}
