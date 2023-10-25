#pragma once

#include "../AccessState.hpp"

namespace Kokoha
{
	/// <summary>
	/// ゲーム開始時のAccessState
	/// </summary>
	class StartingAccessState : public AccessState
	{
	private:

		// 0 のとき 文字を揺らす
		int32 m_noiseCount;

		// プレイヤーのいる座標
		Vec2 m_playerPos;

		// PlayingStateへ遷移するとき true
		bool m_nextStateFlag;

		// ステージ名
		static String stageName;

		// 生成するAccessObjectのリスト
		std::list<AccessObject::Ptr> m_makeObjectList;

	public:

		StartingAccessState(const String& argStageName);

		StartingAccessState();

	private:

		void input(const Vec2& cursorPos) override;

		Optional<std::shared_ptr<AccessState>> update(
			AccessObject::GuidToObject& objectMap,
			AccessObject::TypeToGuidSet& typeToGuidSet,
			BoardRequest&) override;

		bool isUpdatingObject() const override;

		void draw() const override;

		void setMakeObjectList();

	};
}
