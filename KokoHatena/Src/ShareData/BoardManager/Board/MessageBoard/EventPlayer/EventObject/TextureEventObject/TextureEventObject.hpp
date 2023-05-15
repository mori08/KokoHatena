#pragma once

#include "../EventObject.hpp"
#include "../../../../../../../MyLibrary/Linearly/Linearly.hpp"
#include "../../../../../../../MyLibrary/SliceTexture/SliceTexture.hpp"

namespace Kokoha
{
	/// <summary>
	/// �摜��\������EventPlayer�p�I�u�W�F�N�g
	/// </summary>
	class TextureEventObject : public EventObject
	{
	private:

		/// <summary>
		/// �\������摜�̏��
		/// </summary>
		class Slice
		{
		public:
			double time;   // �摜��\�����鎞��
			int32  id;     // �\������摜�̔ԍ��i�����牽�Ԗڂ��j
			bool   mirror; // true �Ȃ� ���] , false �Ȃ� ���]
			Slice(double t, int32 i, bool m)
				: time(t), id(i), mirror(m)
			{
			}
		};

	private:

		// �\��������W
		Linearly<Vec2> m_pos;

		// �\������摜�f�[�^
		SliceTexture m_texture;

	public:

		TextureEventObject(const TOMLValue& param);

		void receive(const TOMLValue& param) override;

		void update() override;

		void draw() const override;

	private:

		/// <summary>
		/// TOMLValue��Point�ɕύX����
		/// </summary>
		/// <param name="toml"> �ݒ�t�@�C���f�[�^ </param>
		/// <returns> ���W </returns>
		static Point tomlToPos(const TOMLValue& toml);

	};
}
