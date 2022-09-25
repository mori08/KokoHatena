#include "MessageBoard.hpp"
#include "../../../../Config/Config.hpp"
#include "../../../../MyLibrary/MyLibrary.hpp"

namespace Kokoha
{
	MessageBoard::MessageBoard()
		: Board(Role::MESSAGE
			, U"MessageBoard"
			, State::IS_HIDING
		)
	{
		m_speakerNameList = Config::getArray<String>(U"MessageBoard.speakerNameList");
	}

	void MessageBoard::receiveRequest(const String&)
	{

	}

	Board::BoardRequest MessageBoard::inputInBoard()
	{
		return none;
	}

	void MessageBoard::updateInBoard()
	{
	}

	void MessageBoard::drawInBoard() const
	{
		// �E���̉�b��ʂ͈̔�
		static const Rect TALK_PAGE_RECT = Config::get<Rect>(U"MessageBoard.talkPageRect");
		// ��b��ʂ͈̔͂�`�悷�鑾��
		static const double TALK_PAGE_THICKNESS = Config::get<double>(U"MessageBoard.talkPageThickness");
		// ��b��ʂ͈̔͂�`�悷��F
		static const ColorF TALK_PAGE_COLOR = Config::get<ColorF>(U"MessageBoard.talkPageColor");

		for (size_t index : Range(0, m_speakerNameList.size() - 1))
		{
			FontAsset(U"20")(m_speakerNameList[index]).draw(getSpeakerNamePos((int32)index), MyWhite);
		}

		TALK_PAGE_RECT.drawFrame(TALK_PAGE_THICKNESS, 0, TALK_PAGE_COLOR);
	}

	Point MessageBoard::getSpeakerNamePos(int32 index)
	{
		// ��ԏ�̖��O�̍��W
		static const Point SPEAKER_NAME_POS = Config::get<Point>(U"MessageBoard.speakerNamePos");
		
		return
			SPEAKER_NAME_POS
			+ Point::Down(index * FontAsset(U"20").height());
	}

}