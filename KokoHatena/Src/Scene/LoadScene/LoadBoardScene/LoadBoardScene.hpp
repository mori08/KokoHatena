#pragma once

#include "../LoadScene.hpp"

namespace Kokoha
{
	/// <summary>
	/// Recordの内容からBoardを生成するシーン
	/// </summary>
	class LoadBoardScene : public LoadScene
	{
	public:

		LoadBoardScene(const InitData& init);

	};
}
