#pragma once

#include "../Scene.hpp"
#include "../../ShareData/BoardManager/Board/AccessBoard/AccessBoard.hpp"

namespace Kokoha
{
	class LastBattleScene : public MyApp::Scene
	{
	private:

		AccessBoard m_accessBoard;

		bool m_isCoding;

		Array<String> m_allCode;

		std::list<String> m_codeList;

		size_t m_row;

		double m_column;

		double m_kioku;

	public:

		LastBattleScene(const InitData& init);

	private:

		void update() override;

		void draw() const override;

	};
}
