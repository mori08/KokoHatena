#pragma once

#include "../AccessObject.hpp"

namespace Kokoha
{
	class PlayerAccessObject : public AccessObject
	{
	private:

		// input�Ō��肷��ړ���
		Vec2 m_movement;

		// true �̂Ƃ������̎�����Ƃ炷 , false �̂Ƃ��������Ƃ炷
		bool m_lightMode;

		// �����o������
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
		/// ���̏��̓���
		/// </summary>
		void inputLight();

	};
}