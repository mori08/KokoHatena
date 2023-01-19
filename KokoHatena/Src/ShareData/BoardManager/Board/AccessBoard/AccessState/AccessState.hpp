#pragma once

#include "../AccessObject/AccessObject.hpp"

namespace Kokoha
{
	class AccessState
	{
	public:

		/// <summary>
		/// �X�V
		/// </summary>
		/// <param name="objectMap"> guid����Object�ւ̘A�z�z�� </param>
		/// <param name="typeToGuidSet"> Object�̎�ނ���guid�ւ̘A�z�z�� </param>
		/// <returns> ����AccessState�ւ�unique_ptr , ��Ԃ�ύX���Ȃ��Ƃ� none </returns>
		virtual Optional<std::shared_ptr<AccessState>> update(
			const AccessObject::GuidToObject& objectMap, 
			const AccessObject::TypeToGuidSet& typeToGuidSet) = 0;

		/// <summary>
		/// �I�u�W�F�N�g���X�V���邩
		/// </summary>
		/// <returns> trur�̂Ƃ��͍X�V , false�̂Ƃ��͍X�V���Ȃ� </returns>
		virtual bool isUpdatingObject() const { return true; }

		/// <summary>
		/// �`��
		/// </summary>
		virtual void draw() const = 0;

	};
}