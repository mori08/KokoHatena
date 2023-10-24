#include "MessageEventObject.hpp"
#include "../../../../../../../Config/Config.hpp"
#include "../../../../../../../MyLibrary/MyLibrary.hpp"

namespace Kokoha
{
	/*
	* Post
	*/
	MessageEventObject::Post::Post(bool isMine, const String& text)
		: m_isMine(isMine)
		, m_text(text)
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

	Rect MessageEventObject::Post::getRect() const
	{
		// 長方形をx軸方向に広げる幅
		static const int32 WIDTH_SPREAD = Config::get<int32>(U"MessageEventObject.widthSpread");

		return Rect(
			m_pos.x - WIDTH_SPREAD,
			m_pos.y,
			m_textRectSize + Size::Right(2 * WIDTH_SPREAD)
		);
	}

	void MessageEventObject::Post::draw(const ColorF& rectColor, const ColorF& textColor) const
	{
		static const String FONT_NAME = Config::get<String>(U"MessageEventObject.fontName");
		static const int32 FONT_HEIGHT = FontAsset(FONT_NAME).height();

		// 長方形をx軸方向に広げる幅
		static const int32 WIDTH_SPREAD = Config::get<int32>(U"MessageEventObject.widthSpread");

		int32 y = m_pos.y;

		getRect().draw(rectColor);
		for (const String row : m_rowList)
		{
			FontAsset(FONT_NAME)(row).draw(m_pos.x, y, textColor);
			y += FONT_HEIGHT;
		}
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

			const int32 width = (int32)FontAsset(FONT_NAME)(subText.substr(0, m)).region().w;

			if (width > MAX_TEXT_RECT_WIDTH) { r = m; }
			else { l = m; }
		}

		m_rowList.emplace_back(subText.substr(0, l));
		splitTextFromWidth(subText.substr(l));
	}

	/*
	* Select
	*/
	MessageEventObject::Select::Select(const TOMLValue& selectTomlAry)
		: m_textAlpha(0)
	{
		for (const auto& selectToml : selectTomlAry.tableArrayView())
		{
			const String text = selectToml[U"text"].getString();
			const String flagName = selectToml[U"flag"].getString();

			m_selectAry.emplace_back(true, text);
			m_flagNameMap[text] = flagName;
		}
	}

	void MessageEventObject::Select::setPosY(int32 y)
	{
		static const int32 SELECT_WIDTH = Config::get<int32>(U"MessageBoard.size.x");
		static const int32 POST_Y = Config::get<int32>(U"MessageEventObject.postY");

		for (Post& post : m_selectAry)
		{
			y += POST_Y;
			post.setPosY(y);
			
			y += post.getSize().y;
		}
	}

	Optional<String> MessageEventObject::Select::input(const Vec2& cursorPos)
	{
		for (const Post& post : m_selectAry)
		{
			if (post.getRect().intersects(cursorPos) && MouseL.down())
			{
				return m_flagNameMap[post.getText()];
			}
		}

		return none;
	}

	void MessageEventObject::Select::update()
	{
		static const double TEXT_CHANGE_ALPHA_RATE = Config::get<double>(U"MessageEventObject.textChangeAlphaRate");

		internalDividingPoint(m_textAlpha, 1.0, TEXT_CHANGE_ALPHA_RATE);
	}

	void MessageEventObject::Select::draw() const
	{
		for (const auto& select : m_selectAry)
		{
			select.draw(AlphaF(0), ColorF(MyWhite, m_textAlpha));
		}
	}

	/*
	* MessageEventObject
	*/
	MessageEventObject::MessageEventObject(const TOMLValue&)
		: m_select(none)
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

			m_postList.emplace_back(speaker, text);
			static const size_t MAX_POST_COUNT = Config::get<size_t>(U"MessageEventObject.maxPostCount");
			if (m_postList.size() > MAX_POST_COUNT)
			{
				m_postList.pop_front();
			}
			updatePostPos();

			// 一文字ごとにかかる待ち時間
			static const double WAIT_SECOND_PER_CHAR_COUNT = Config::get<double>(U"MessageEventObject.waitSecondPerCharCount");
			m_waitSecond = WAIT_SECOND_PER_CHAR_COUNT * text.size();

			return;
		}

		if (type == U"select")
		{
			m_select = Select(param[U"select"]);
			updatePostPos();

			return;
		}
	}

	bool MessageEventObject::wait() const
	{
		// 投稿待ち
		if (m_waitSecond > 0)
		{
			return true;
		}

		// 選択中
		if (m_select)
		{
			return true;
		}

		return false;
	}

	void MessageEventObject::input(const Vec2& cursorPos)
	{
		if (m_select)
		{
			auto flagNameOpt = m_select->input(cursorPos);

			if (flagNameOpt)
			{
				m_updateJumpFlagMap[flagNameOpt.value()] = true;
				m_select = none;
			}
		}
	}

	void MessageEventObject::update()
	{
		m_waitSecond -= Scene::DeltaTime();

		if (m_select)
		{
			m_select->update();
		}
	}

	void MessageEventObject::draw() const
	{
		static const ColorF POST_RECT_COLOR = Config::get<ColorF>(U"MessageEventObject.postRectColor");

		for (const Post& post : m_postList)
		{
			post.draw(POST_RECT_COLOR, MyBlack);
		}

		if (m_select)
		{
			m_select->draw();
		}
	}

	void MessageEventObject::updatePostPos()
	{
		static const int32 POST_Y = Config::get<int32>(U"MessageEventObject.postY");

		int32 y = 0;
		for (Post& post : m_postList)
		{
			y += POST_Y;
			post.setPosY(y);
			y += post.getSize().y;
		}

		if (m_select)
		{
			m_select->setPosY(y);
		}
	}
}
