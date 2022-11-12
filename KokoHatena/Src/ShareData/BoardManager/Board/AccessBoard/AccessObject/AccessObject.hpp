#pragma once

#include "../Terrain/Terrain.hpp"
#include "AccessLight/AccessLight.hpp"

namespace Kokoha
{
	/// <summary>
	/// AccessBoard�Ŏg�p�����Object
	/// </summary>
	class AccessObject
	{
	public:

		enum class Type
		{
			PLAYER, // �v���C���[
			ENEMY,  // �G
			LIGHT,  // ��
			GOAL    // �S�[��
		};

		using Ptr = std::unique_ptr<AccessObject>;

		using GuidToObject = std::unordered_map<String, Ptr>;

		using TypeToGuidSet = std::unordered_map<Type, std::unordered_set<String>>;

	private:

		// �I�u�W�F�N�g�̎��
		const Type m_type;

		// GUID
		const String m_guid;

		// true �̂Ƃ� �폜����
		bool m_isErase;

		// �쐬����I�u�W�F�N�g�̃��X�g
		std::list<AccessObject::Ptr> m_makeObjectList;

		// �ʒu�Ɣ���p�͈̔�
		Circle m_body;

		// ��
		AccessLight m_light;
		
	public:

		AccessObject(const Type& type, const Circle& body);

		AccessObject(const Type& type, const Vec2& pos);

		virtual ~AccessObject() {}

		/// <summary>
		/// type�̎擾
		/// </summary>
		/// <returns> type </returns>
		const Type& type() const
		{
			return m_type;
		}

		/// <summary>
		/// guid�̎擾
		/// </summary>
		/// <returns> guid </returns>
		const String& guid() const
		{
			return m_guid;
		}

		/// <summary>
		/// body�̎擾
		/// </summary>
		/// <returns> body </returns>
		const Circle& body() const
		{
			return m_body;
		}

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
		/// <param name="guidToObject"> guid����I�u�W�F�N�g�ւ̘A�z�z�� </param>
		/// <param name="typeToGuidSet"> �I�u�W�F�N�g�̎�ނ���guid�ւ̘A�z�z�� </param>
		virtual void checkOthers(const Terrain& terrain, const GuidToObject& guidToObject, const TypeToGuidSet& typeToGuidSet);

		/// <summary>
		/// �ǉ��I�u�W�F�N�g���I�u�W�F�N�g���X�g�ɒǉ�
		/// </summary>
		/// <param name="makeObjectList"> �I�u�W�F�N�g�̍쐬���X�g </param>
		virtual void addObjectList(std::list<AccessObject::Ptr>& makeObjectList);

		/// <summary>
		/// �폜����
		/// </summary>
		/// <returns> true �̂Ƃ��폜 </returns>
		virtual bool isEraseAble() const;

		/// <summary>
		/// �`��
		/// </summary>
		virtual void draw() const;

		/// <summary>
		/// ���̕`��
		/// </summary>
		virtual void drawLight() const;

	protected:

		/// <summary>
		/// ���̃I�u�W�F�N�g���폜����
		/// </summary>
		void erase()
		{
			m_isErase = true;
		}

		/// <summary>
		/// ���̃I�u�W�F�N�g���쐬����
		/// </summary>
		/// <param name="objectPtr"> �쐬����I�u�W�F�N�g��unique_ptr </param>
		void makeObject(AccessObject::Ptr&& object)
		{
			m_makeObjectList.emplace_back(std::move(object));
		}

		/// <summary>
		/// �ړ�
		/// </summary>
		/// <param name="movement"> �ړ���(/s) </param>
		/// <param name="terrain"> �n�` </param>
		/// <returns> ���ۂɈړ������ړ��� </returns>
		Vec2 walk(Vec2 movement, const Terrain& terrain);

		/// <summary>
		/// �ړI�n�ւ̈ړ�
		/// </summary>
		/// <param name="speed"> ����(/s) </param>
		/// <param name="goal"> �ړI�n </param>
		/// <param name="terrain"> �n�` </param>
		/// <returns> ���ۂɈړ������ړ��� </returns>
		Vec2 walkToGoal(double speed, const Vec2& goal, const Terrain& terrain);

		/// <summary>
		/// ��
		/// </summary>
		/// <returns> ���̎Q�� </returns>
		AccessLight& light()
		{
			return m_light;
		}

	};
}