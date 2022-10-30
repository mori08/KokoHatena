#pragma once

#include "../EventObject.hpp"

namespace Kokoha
{
	/// <summary>
	/// �摜��\������EventPlayer�p�I�u�W�F�N�g
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
