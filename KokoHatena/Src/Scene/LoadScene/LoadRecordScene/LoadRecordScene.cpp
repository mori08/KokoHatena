#include"LoadRecordScene.hpp"

namespace Kokoha
{
	LoadRecordScene::LoadRecordScene(const InitData& init)
		: LoadScene(init)
	{
		setLoadThread
		(
			[]()
			{
				return SceneName::DESKTOP;
			}
		);
	}
}