#pragma once

#include "../EventObject.hpp"

namespace Kokoha
{
	/// <summary>
	/// 画像を表示するEventPlayer用オブジェクト
	/// </summary>
	class TextureEventObject : public EventObject
	{
	public:

		TextureEventObject(const TOMLValue& param);

		void receive(const TOMLValue& param) override;

		void update() override;

		void draw() const override;

	};
}
