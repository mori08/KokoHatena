#pragma once

#include "../Terrain/Terrain.hpp"

namespace Kokoha
{
	/// <summary>
	/// AccessBoard�Ŏg�p�����Object
	/// </summary>
	class AccessObject
	{
	public:

		using Ptr = std::unique_ptr<AccessObject>;

		enum class Type
		{
			PLAYER // �v���C���[
		};

	private:

		// �I�u�W�F�N�g�̎��
		const Type m_type;

		// GUID
		const String m_guid;

		// �ʒu�Ɣ���p�͈̔�
		Circle m_body;
		
	public:

		AccessObject(const Type& type, const Circle& body);

		virtual ~AccessObject() {}

		/// <summary>
		/// ����
		/// </summary>
		/// <param name="cursorPos"> �J�[�\���̍��W </param>
		virtual void input(const Vec2& cursorPos);

		/// <summary>
		/// �X�V
		/// </summary>
		/// <param name="terrain"> �n�` </param>
		virtual void update(const Terrain& terrain);

		/// <summary>
		/// ���I�u�W�F�N�g�̊m�F
		/// </summary>
		/// <param name="terrain"> �n�` </param>
		/// <param name="objectMap"> guid����I�u�W�F�N�g�ւ̘A�z�z�� </param>
		/// <param name="typeMap"> �I�u�W�F�N�g�̎�ނ���guid�ւ̘A�z�z�� </param>
		virtual void checkOthers(const Terrain& terrain, const std::unordered_map<String, Ptr>& objectMap, const std::unordered_map<Type, std::list<String>>& typeMap);

		/// <summary>
		/// �`��
		/// </summary>
		virtual void draw() const;

		/// <summary>
		/// ���̕`��
		/// </summary>
		virtual void drawLight() const;

		/// <summary>
		/// �폜����
		/// </summary>
		/// <returns> true �̂Ƃ��폜 </returns>
		virtual bool isEraseAble() const;

	};
}