#include "MessageEventObject.hpp"
#include "../../../../../../../Config/Config.hpp"

namespace Kokoha
{
	MessageEventObject::Post::Post(bool isMine, const String& text)
		: m_isMine(isMine)
	{
		static const String FONT_NAME = Config::get<String>(U"MessageEventObject.fontName");
		static const int32 FONT_HEIGHT = FontAsset(FONT_NAME).height();
		static const int32 MAX_TEXT_RECT_WIDTH = Config::get<int32>(U"MessageEventObject.maxTextRectWidth");
		
		for (const String& subText : text.split(U'\n'))
		{
			splitTextFromWidth(subText);
		}

		for (const String& row : m_rowList)
		{
			m_textRectSize.x = Max(m_textRectSize.x, (int32)FontAsset(FONT_NAME)(row).region().w);
		}

		m_textRectSize.x = Min(m_textRectSize.x, MAX_TEXT_RECT_WIDTH);
		m_textRectSize.y = FONT_HEIGHT * (int32)m_rowList.size();

		static const int32 POST_X = Config::get<int32>(U"MessageEventObject.postX");
		static const int32 MINE_X = Config::get<int32>(U"MessageBoard.size.x") - Config::get<int32>(U"MessageBoard.speakerNameWidth");
		m_pos.x = m_isMine
			? MINE_X - m_textRectSize.x - POST_X
			: POST_X;
		m_pos.y = 0;
	}

	void MessageEventObject::Post::splitTextFromWidth(const String& subText)
	{
		static const String FONT_NAME = Config::get<String>(U"MessageEventObject.fontName");
		static const int32 MAX_TEXT_RECT_WIDTH = Config::get<int32>(U"MessageEventObject.maxTextRectWidth");

		// 文字列が指定した幅に収まるならそのまま追加
		if (FontAsset(FONT_NAME)(subText).region().w < MAX_TEXT_RECT_WIDTH)
		{
			m_rowList.emplace_back(subText);
			return;
		}
		size_t l = 0;
		size_t r = subText.size();

		// 幅に収まる文字数を二分探索で計算して追加
		while (r - l > 1)
		{
			const size_t m = (l + r) / 2;

			const int32 width = FontAsset(FONT_NAME)(subText.substr(0, m)).region().w;

			if (width > MAX_TEXT_RECT_WIDTH) { r = m; }
			else { l = m; }
		}

		m_rowList.emplace_back(subText.substr(0, l));
		splitTextFromWidth(subText.substr(l));
	}

	void MessageEventObject::Post::draw(int32 posY) const
	{
		static const String FONT_NAME = Config::get<String>(U"MessageEventObject.fontName");
		static const int32 FONT_HEIGHT = FontAsset(FONT_NAME).height();

		// 長方形をx軸方向に広げる幅
		static const int32 WIDTH_SPREAD = Config::get<int32>(U"MessageEventObject.widthSpread");

		int32 y = posY;

		Rect(m_pos.x - WIDTH_SPREAD, y, m_textRectSize + Size::Right(2 * WIDTH_SPREAD)).draw(Palette::Gray);
		for (const String row : m_rowList)
		{
			FontAsset(FONT_NAME)(row).draw(m_pos.x, y);
			y += FONT_HEIGHT;
		}
	}

	MessageEventObject::MessageEventObject(const TOMLValue&)
		: m_postArg(none)
		, m_waitSecond(0)
	{
	}

	void MessageEventObject::receive(const TOMLValue& param)
	{
		const String type = param[U"type"].getString();

		if (type == U"message")
		{
			const String text = param[U"text"].getString();
			const bool   speaker = param[U"speaker"].get<bool>();
			m_postArg = std::pair<bool, String>(speaker, text);

			// 一文字ごとにかかる待ち時間
			static const double WAIT_SECOND_PER_CHAR_COUNT = Config::get<double>(U"MessageEventObject.waitSecondPerCharCount");
			m_waitSecond = WAIT_SECOND_PER_CHAR_COUNT * text.size();
		}
	}

	bool MessageEventObject::wait() const
	{
		if (m_postArg)
		{
			return true;
		}

		return false;
	}

	void MessageEventObject::update()
	{
		m_waitSecond -= Scene::DeltaTime();
		if (m_waitSecond < 0 && m_postArg)
		{
			m_postList.emplace_back(m_postArg->first, m_postArg->second);
			m_postArg = none;

			static const size_t MAX_POST_COUNT = Config::get<size_t>(U"MessageEventObject.maxPostCount");
			if (m_postList.size() > MAX_POST_COUNT)
			{
				m_postList.pop_front();
			}
		}
	}

	void MessageEventObject::draw() const
	{
		static const int32 POST_Y = Config::get<int32>(U"MessageEventObject.postY");

		int32 y = 0;
		for (const Post& post : m_postList)
		{
			y += POST_Y;
			post.draw(y);
			y += post.getSize().y;
		}
	}
}
