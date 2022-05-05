#pragma once

#include<Siv3D.hpp>

namespace Kokoha
{
	/// <summary>
	/// �����ō쐬�����s�N�Z���V�F�[�_�̊Ǘ�
	/// </summary>
	class MyPixelShader
	{
	private:

		// �����ō쐬�����s�N�Z���V�F�[�_�̃}�b�v
		std::unordered_map<String, const PixelShader> m_shaderMap;

	private:

		MyPixelShader() = default;

		/// <summary>
		/// �N���X���Ŏg�p����C���X�^���X�̎擾
		/// </summary>
		/// <returns> �C���X�^���X </returns>
		static MyPixelShader& instance()
		{
			static MyPixelShader myShader;
			return myShader;
		}

	public:

		/// <summary>
		/// �s�N�Z���V�F�[�_�̓ǂݎ��
		/// </summary>
		static void loadPixelShader();

		/// <summary>
		/// �s�N�Z���V�F�[�_�̎擾
		/// </summary>
		/// <param name="type"> ���O </param>
		/// <returns> �s�N�Z���V�F�[�_ </returns>
		static const PixelShader& get(const String& name);

	};
}