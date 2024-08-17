#include "LastBattleScene.hpp"
#include "../../MyLibrary/MyLibrary.hpp"
#include "../../Config/Config.hpp"

namespace Kokoha
{
	LastBattleScene::LastBattleScene(const InitData& init)
		: IScene(init)
		, m_accessBoard(U"last")
		, m_isCoding(false)
		, m_isEnding(false)
		, m_row(0)
		, m_column(0)
		, m_kioku(0)
	{
		TextReader reader(U"asset/data/coding.txt");

		while (const auto line = reader.readLine())
		{
			m_allCode.emplace_back(line.value());
		}
	}

	void LastBattleScene::update()
	{
		m_accessBoard.input();

		BoardRequest boardRequest;
		m_accessBoard.update(boardRequest);

		for (const auto& toBoard : boardRequest.toBoard)
		{
			if (toBoard.first == BoardRole::MESSAGE
				&& toBoard.second == U"access"
				&& !m_isEnding)
			{
				m_isEnding = true;
				m_kioku = 0;
			}
			else
			{
				m_isCoding = true;
			}
		}

		if (m_isCoding || m_isEnding)
		{
			static const double WORDS_PER_TIME = Config::get<double>(U"LastAccessState.wordsPerTime");
			m_kioku += WORDS_PER_TIME * Scene::DeltaTime();
		}
		if (m_isCoding)
		{
			m_column += 60 * Scene::DeltaTime();
			if (m_column > m_allCode[m_row].length())
			{
				m_codeList.emplace_front(m_allCode[m_row]);
				m_column = 0;
				m_row = (m_row + 1) % m_allCode.size();
			}
		}
		if (m_isEnding && m_kioku > 90)
		{
			changeScene(SceneName::ENDING);
		}
	}

	void LastBattleScene::draw() const
	{
		const double HEIGHT = FontAsset(U"10").height();
		Vec2 pos(0, Scene::Height() - HEIGHT);
		FontAsset(U"10")(m_allCode[m_row].substr(0, (size_t)m_column)).draw(pos, MyWhite);
		pos.y -= HEIGHT;

		for (const auto& code : m_codeList)
		{
			FontAsset(U"10")(code).draw(pos, myColor(0.5));
			pos.y -= HEIGHT;
		}

		m_accessBoard.draw();

		if (m_isEnding)
		{
			static const String ENDING_WORDS = U"あなたの勝ちです   \nハカセの研究所に来てください   \n扉は開けておきます   ";
			FontAsset(U"18")(ENDING_WORDS.substr(0, (size_t)m_kioku)).draw(Vec2(), MyWhite);
		}
		else
		{
			static const String KIOKU_WORDS = U"...？     \n...なるほど、光の動きを書きかえてますね   \n流石、元助手です    ";
			if (m_kioku < KIOKU_WORDS.size())
			{
				FontAsset(U"18")(KIOKU_WORDS.substr(0, (size_t)m_kioku)).draw(Vec2(), MyWhite);
			}
		}
	}
}
