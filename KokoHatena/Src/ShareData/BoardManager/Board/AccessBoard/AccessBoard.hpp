#pragma once
#include"../Board.hpp"
#include"AccessObject/AccessObject.hpp"
#include"Terrain/Terrain.hpp"

namespace Kokoha
{
	class AccessBoard : public Board
	{
	private:

		Terrain m_terrain;

	public:

		AccessBoard();

	private:

		void receiveRequest(const String& requestText) override;

		void inputInBoard() override;

		void updateInBoard(BoardRequest& request) override;

		void drawInBoard() const override;

	};
}