#pragma once

#include"../LoadScene.hpp"

namespace Kokoha
{
	/// <summary>
	/// RecordManagerの内容の読み込み
	/// 他Managerのセットアップも行う
	/// </summary>
	class LoadRecordScene : public LoadScene
	{
	public:

		LoadRecordScene(const InitData& init);

	};
}
