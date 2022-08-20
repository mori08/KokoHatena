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
	public:

		// ���R�[�h��ۑ�����t�@�C����
		static const String FILE_NAME;

	private:

		// Record�̃}�b�v
		std::map<String, Record> m_recordMap;

		// ���Ԃ�\��������
		String m_timeCode;

	public:

		/// <summary>
		/// Record���f�t�H���g�l�Őݒ�
		/// </summary>
		RecordSet();

		/// <summary>
		/// �Í����𕜍����A�t���O�̃��X�g�Ɋi�[����
		/// </summary>
		/// <param name="str"> �Í������ꂽ������ </param>
		static Optional<RecordSet> decryption(const String& str);

		/// <summary>
		/// ���R�[�h�̈Í���
		/// </summary>
		/// <returns> �Í������������� </returns>
		String encryption() const;

		/// <summary>
		/// ���R�[�h�̐ݒ�
		/// </summary>
		/// <param name="name"> ���O </param>
		/// <param name="value"> �ύX��̒l </param>
		/// <returns> *this </returns>
		RecordSet& setRecord(const String& name, int32 value);

		/// <summary>
		/// ���R�[�h�Ɍ��݂̎�����ݒ肷��
		/// </summary>
		/// <returns> *this </returns>
		RecordSet& setRecordTime();

		/// <summary>
		/// ���R�[�h�̎擾
		/// </summary>
		/// <param name="name"> ���O </param>
		/// <returns> ���R�[�h�̒l </returns>
		int32 getRecord(const String& name) const;

		/// <summary>
		/// �`��
		/// </summary>
		/// <param name="pos"> ���W </param>
		void draw(const Point& pos) const;

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

	};
}