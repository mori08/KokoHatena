#pragma once

#include "Record/Record.hpp"

namespace Kokoha
{
	/// <summary>
	/// ���R�[�h�i�Z�[�u�f�[�^�j�̃��[�h��Z�[�u�C
	/// �t���O�␔�l�̕ύX�C�擾���s��
	/// </summary>
	class RecordManager
	{
	public:

		enum class LoadResult
		{
			NEW_GAME,  // YOUR_RECORD.txt�����݂��Ȃ��Ƃ�
			LOAD_GAME, // YOUR_RECORD.txt�𐳂����ǂݍ��߂��Ƃ�
			ERROR      // YOUR_RECORD.txt���ǂݍ��߂Ȃ������Ƃ�
		};

	private:

		// ���R�[�h�̃}�b�v
		std::map<String, Record> m_recordMap;

		// �����̍��v
		const int32 m_totalDigit;

	public:

		RecordManager();

		/// <summary>
		/// �Z�[�u�f�[�^�p�t�@�C�����烍�[�h
		/// </summary>
		/// <returns> ���[�h�̌��� </returns>
		LoadResult load();

		/// <summary>
		/// �S���R�[�h�̏�����
		/// </summary>
		void initAllRecord();

		/// <summary>
		/// �Z�[�u�f�[�^�p�t�@�C���ɃZ�[�u
		/// </summary>
		void save();

		/// <summary>
		/// ���R�[�h�̐ݒ�
		/// </summary>
		/// <param name="name" > ���O         </param>
		/// <param name="value"> �ύX�������l </param>
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
		void writeDebugText() const
		{
#ifdef _DEBUG
			TextWriter writer(U"asset/data/debug.txt");
			char32 initChar = U'z';
			for (const auto& record : m_recordMap)
			{
				if (record.first[0] != initChar)
				{
					initChar = record.first[0];
					writer.writeln(String(U"\n[ ") + initChar + U" ]");
				}
				writer.writeln(Pad(ToString(record.second.get()), { 4,U' ' }) + U" < [" + record.first + U"]");
			}
			writer.close();
#endif // _DEBUG
		}

	private:

		/// <summary>
		/// m_recordMap�ɕK�v�ƂȂ�Record��S�ēo�^
		/// </summary>
		/// <returns> ���v���� </returns>
		int32 setAllRecordToMap();

		/// <summary>
		/// ���R�[�h�̈Í���
		/// </summary>
		/// <returns> �Í������� </returns>
		String encryption() const;

		/// <summary>
		/// �Í����𕜍��C�t���O�̃��X�g�Ɋi�[
		/// </summary>
		/// <param name="str"> �Í��� </param>
		/// <returns> �����ɐ��������Ƃ� true , �����łȂ��Ƃ� false </returns>
		bool decryption(const String& str);

	};
}