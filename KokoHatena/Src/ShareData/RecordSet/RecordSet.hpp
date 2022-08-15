#pragma once

#include"Record/Record.hpp"

namespace Kokoha
{
	/// <summary>
	/// ������Record���Ǘ����A
	/// ������Ƃ̕ϊ��A�eRecord�̕ύX/�擾���s��
	/// </summary>
	class RecordSet
	{
	private:

		// Record�̃}�b�v
		std::map<String, Record> m_recordMap;

		// �ǂݍ��݂Ɏ��s���Ă���Ƃ� true , �����łȂ��Ƃ� false
		bool m_isError;

	public:

		/// <summary>
		/// Record���f�t�H���g�l�Őݒ�
		/// </summary>
		RecordSet();

		/// <summary>
		/// ������𕜍���Record�ɐݒ�
		/// </summary>
		/// <param name="text"></param>
		RecordSet(const String& str);

		/// <summary>
		/// ������ւ̕ϊ�
		/// </summary>
		/// <returns> �G���[�Ȃ� none , �����łȂ��Ȃ�Í������������� </returns>
		Optional<String> toString() const;

		/// <summary>
		/// ���R�[�h�̐ݒ�
		/// </summary>
		/// <param name="name"> ���O </param>
		/// <param name="value"> �ύX��̒l </param>
		void setRecord(const String& name, int32 value);

		/// <summary>
		/// ���R�[�h�̎擾
		/// </summary>
		/// <param name="name"> ���O </param>
		/// <returns> ���R�[�h�̒l </returns>
		int32 getRecord(const String& name) const;

		/// <summary>
		/// �e�L�X�g�t�@�C���Ƀ��R�[�h�̓��e����������
		/// </summary>
		void writeDebugText() const;

	private:

		/// <summary>
		/// �����l���i�[����Record�̃}�b�v���擾�i����̂�TOML�t�@�C���̓ǂݍ��݁j
		/// </summary>
		/// <returns> �����l���i�[����Record�̃}�b�v </returns>
		const std::map<String, Record>& getDefaultRecordMap() const;

		/// <summary>
		/// ���R�[�h�̈Í���
		/// </summary>
		/// <returns> �Í������� </returns>
		String encryption() const;

		/// <summary>
		/// �Í����𕜍����A�t���O�̃��X�g�Ɋi�[����
		/// </summary>
		/// <param name="str"></param>
		void decryption(const String& str);

	};
}