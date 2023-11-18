#include "MessageBoard.hpp"
#include "../../../../Config/Config.hpp"
#include "../../../../MyLibrary/MyLibrary.hpp"

namespace Kokoha
{
	MessageBoard::MessageBoard(const RecordSet& recordSet)
		: Board(BoardRole::MESSAGE
			, U"MessageBoard"
			, BoardState::IS_HIDING
		)
		, m_selectedSpeakerName(none)
		, m_recordDay(recordSet.getRecord(U"Day"))
	{
		static const Array<String> SPEAKER_NAME_LIST = Config::getArray<String>(U"MessageBoard.speakerNameList");
		m_speakerNameList = SPEAKER_NAME_LIST;

		for (const auto& speakerName : m_speakerNameList)
		{
			m_eventPlayerMap.try_emplace
			(
				speakerName,
				EventPlayer
				(
					U"asset/data/event/" + speakerName + U".toml",
					Size(size().x - getSpeakerNameRect(0).w, size().y),
					recordSet
				)
			);

			m_notReadSpeakerNameSet.insert(speakerName);
		}

		m_eventPlayerMap.try_emplace
		(
			U"ロボット",
			EventPlayer
			(
				U"asset/data/event/day" + ToString(m_recordDay) + U".toml",
				Size(size().x - getSpeakerNameRect(0).w, size().y),
				recordSet
			)
		);

		if (m_recordDay != 0)
		{
			m_speakerNameList.emplace_back(U"ロボット");
		}
	}

	void MessageBoard::receiveRequest(const String& requestText)
	{
		for (auto& eventPlayer : m_eventPlayerMap)
		{
			eventPlayer.second.receive(requestText);
		}
	}

	void MessageBoard::inputInBoard()
	{
		// 話し相手の選択
		for (size_t index : Range(0, m_speakerNameList.size() - 1))
		{
			if (MouseL.down() && getSpeakerNameRect((int32)index).contains(cursorPosInBoard()))
			{
				const String speakerName = m_speakerNameList[index];
				m_selectedSpeakerName = speakerName;

				if (m_notReadSpeakerNameSet.count(speakerName))
				{
					m_notReadSpeakerNameSet.erase(speakerName);

					if (m_recordDay == 0 && m_notReadSpeakerNameSet.empty())
					{
						m_speakerNameList.emplace_back(U"ロボット");
					}
				}
			}
		}

		if (m_selectedSpeakerName)
		{
			m_eventPlayerMap.find(m_selectedSpeakerName.value())->second.input(boardArg());
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
		// 会話画面の範囲を描画する太さ
		static const double TALK_PAGE_THICKNESS = Config::get<double>(U"MessageBoard.talkPageThickness");
		// 会話画面の範囲を描画する色
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
		// 幅
		static const int32 SPEAKER_NAME_WIDTH = Config::get<int32>(U"MessageBoard.speakerNameWidth");

		return Rect(
			Point::Down(index * FontAsset(U"20").height()),
			SPEAKER_NAME_WIDTH,
			FontAsset(U"20").height()
		);
	}

}
