#pragma once

#include "../AccessObject.hpp"

namespace Kokoha
{
	class PlayerAccessObject : public AccessObject
	{
	private:

		// input‚ÅŒˆ’è‚·‚éˆÚ“®—Ê
		Vec2 m_movement;

		// true ‚Ì‚Æ‚«©•ª‚Ìü‚è‚ğÆ‚ç‚· , false ‚Ì‚Æ‚«‰“‚­‚ğÆ‚ç‚·
		bool m_lightMode;

		// Œõ‚ğo‚·•ûŒü
		double m_direction;

	public:

		PlayerAccessObject(const Vec2& pos);

	private:

		void input(const Vec2& cursorPos) override;

		void update(const Terrain& terrain) override;

		void draw() const override;

		void checkOthers(const Terrain&, const GuidToObject& guidToObject, const TypeToGuidSet& typeToGuidSet) override;

	private:

		/// <summary>
		/// Œõ‚Ìî•ñ‚Ì“ü—Í
		/// </summary>
		void inputLight();

	};
}