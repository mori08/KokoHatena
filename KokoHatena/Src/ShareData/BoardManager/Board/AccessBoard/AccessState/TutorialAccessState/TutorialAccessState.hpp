#pragma once

#include "../PlayingAccessState/PlayingAccessState.hpp"

namespace Kokoha
{
	/// <summary>
	/// チュートリアル用のAccessState
	/// </summary>
	class TutorialAccessState : public PlayingAccessState
	{
	private:

		// 表示文字数(整数にキャストして使う）
		double m_wordsCount;

		// 表示する文字列番号
		size_t m_textId;

		// 文字列を表示する座標
		Vec2 m_textPos;

	public:

		TutorialAccessState();

	private:

		Optional<std::shared_ptr<AccessState>> update(
			AccessObject::GuidToObject& objectMap,
			AccessObject::TypeToGuidSet& typeToGuidSet,
			BoardRequest& boardRequest) override;

		void draw() const override;
	};
}
