#pragma once

#include "../AccessObject/AccessObject.hpp"
#include "../../BoardConst.hpp"

namespace Kokoha
{
	class AccessState
	{
	public:

		virtual ~AccessState() {};

	public:

		/// <summary>
		/// ����
		/// </summary>
		/// <param name="cursorPos"> �J�[�\���̍��W </param>
		virtual void input(const Vec2& cursorPos) = 0;

		/// <summary>
		/// �X�V
		/// </summary>
		/// <param name="objectMap"> guid����Object�ւ̘A�z�z�� </param>
		/// <param name="typeToGuidSet"> Object�̎�ނ���guid�ւ̘A�z�z�� </param>
		/// <param name="typeToGuidSet"> AccessBoard��BoardRequest </param>
		/// <returns> ����AccessState�ւ�unique_ptr , ��Ԃ�ύX���Ȃ��Ƃ� none </returns>
		virtual Optional<std::shared_ptr<AccessState>> update(
			AccessObject::GuidToObject& objectMap, 
			AccessObject::TypeToGuidSet& typeToGuidSet,
			BoardRequest& boradRequest) = 0;

		/// <summary>
		/// �I�u�W�F�N�g���X�V���邩
		/// </summary>
		/// <returns> trur�̂Ƃ��͍X�V , false�̂Ƃ��͍X�V���Ȃ� </returns>
		virtual bool isUpdatingObject() const = 0;

		/// <summary>
		/// �`��
		/// </summary>
		virtual void draw() const = 0;

	protected:

		/// <summary>
		/// �{�[�h�͈̔͂����������`�̎擾
		/// </summary>
		/// <returns> �{�[�h�͈̔͂����������` </returns>
		static const Rect& boardRect();

	};
}