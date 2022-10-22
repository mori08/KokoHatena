#include "MessageBoard.hpp"
#include "../../../../Config/Config.hpp"
#include "../../../../MyLibrary/MyLibrary.hpp"

namespace Kokoha
{
	MessageBoard::MessageBoard()
		: Board(BoardRole::MESSAGE
			, U"MessageBoard"
			, BoardState::IS_HIDING
		)
		, m_selectedSpeakerName(none)
	{
		static const Array<String> SPEAKER_NAME_LIST = Config::getArray<String>(U"MessageBoard.speakerNameList");
		m_speakerNameList = SPEAKER_NAME_LIST;

		for (const auto& speakerName : m_speakerNameList)
		{
			// TODO: Record�̓��e�ɉ�����EventPlayer�ɏ�����
			m_eventPlayerMap.try_emplace
			(
				speakerName,
				EventPlayer
				(
					U"asset/data/event/test.toml", 
					Size(size().x - getSpeakerNameRect(0).w, size().y)
				)
			);
		}
	}

	void MessageBoard::receiveRequest(const String&)
	{
		
	}

	void MessageBoard::inputInBoard()
	{
		// �b������̑I��
		for (size_t index : Range(0, m_speakerNameList.size() - 1))
		{
			if (MouseL.down() && getSpeakerNameRect((int32)index).contains(cursorPosInBoard()))
			{
				m_selectedSpeakerName = m_speakerNameList[index];
			}
		}

		if (m_selectedSpeakerName)
		{
			m_eventPlayerMap.find(m_selectedSpeakerName.value())->second.input();
		}
	}

	void MessageBoard::updateInBoard(BoardRequest& request)
	{
		if (m_selectedSpeakerName)
		{
			m_eventPlayerMap.find(m_selectedSpeakerName.value())->second.update(request);
		}
	}

	void MessageBoard::drawInBoard() const
	{
		static const Point SPEAKER_NAME_POS = Config::get<Point>(U"MessageBoard.speakerNamePos");
		// ��b��ʂ͈̔͂�`�悷�鑾��
		static const double TALK_PAGE_THICKNESS = Config::get<double>(U"MessageBoard.talkPageThickness");
		// ��b��ʂ͈̔͂�`�悷��F
		static const ColorF TALK_PAGE_COLOR = Config::get<ColorF>(U"MessageBoard.talkPageColor");

		for (size_t index : Range(0, m_speakerNameList.size() - 1))
		{
			const Rect rect = getSpeakerNameRect((int32)index);

			if (rect.contains(cursorPosInBoard()))
			{
				rect.draw(TALK_PAGE_COLOR);
			}

			FontAsset(U"20")(m_speakerNameList[index]).draw(rect.pos + SPEAKER_NAME_POS, MyWhite);
		}

		if (m_selectedSpeakerName)
		{
			m_eventPlayerMap.find(m_selectedSpeakerName.value())
				->second.draw(Point(getSpeakerNameRect(0).w, 0));
		}

		Rect(
			getSpeakerNameRect(0).w,
			0,
			size().x - getSpeakerNameRect(0).w,
			size().y
		).drawFrame(TALK_PAGE_THICKNESS, 0, TALK_PAGE_COLOR);
	}

	Rect MessageBoard::getSpeakerNameRect(int32 index)
	{
		// ��
		static const int32 SPEAKER_NAME_WIDTH = Config::get<int32>(U"MessageBoard.speakerNameWidth");

		return Rect(
			Point::Down(index * FontAsset(U"20").height()),
			SPEAKER_NAME_WIDTH,
			FontAsset(U"20").height()
		);
	}

}