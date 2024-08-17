#pragma once
#include "../Scene.hpp"
#include "../../MyLibrary/SliceTexture/SliceTexture.hpp"

namespace Kokoha
{
	class EndingScene : public MyApp::Scene
	{
	private:

		size_t m_textId;

		double m_wordsCount;

		SliceTexture m_radiusTexture;

	public:

		EndingScene(const InitData& init);

	private:

		void update() override;

		void draw() const override;

	private:

		const Array<String>& textList() const;

	};
}
