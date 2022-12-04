#pragma once

#include <Siv3D.hpp>

namespace Kokoha
{
	/// <summary>
	/// �ӂ��쐬���邽�߂̕ӂ̃��X�g
	/// </summary>
	class EdgeList
	{
	public:

		// �� 
		// �����ȕӂ̏ꍇ {x, {y1, y2}}
		// �����ȕӂ̏ꍇ {y, {x1, x2}}
		using Edge = std::pair<int32, std::pair<int32, int32>>;

		// �ӂ̃C�e���[�^
		using ConstItr = std::list<Edge>::const_iterator;

		// �������X�g
		class SubList
		{
		private:

			ConstItr m_beginItr, m_endItr;

		public:

			SubList(ConstItr beginItr, ConstItr endItr) 
				: m_beginItr(beginItr)
				, m_endItr(endItr) 
			{}

			ConstItr begin() const { return m_beginItr; }
			ConstItr end() const { return m_endItr; }
		};

	private:

		// �Ӄ��X�g
		// �z����g���ƃG���[
		std::list<Edge> m_edgeList;

		// �C�e���[�^�̔z��
		Array<ConstItr> m_itrAry;

	public:

		/// <summary>
		/// �ӂ̒ǉ�
		/// </summary>
		/// <param name="edge"> �� </param>
		void addEdge(const Edge& edge)
		{
			m_edgeList.emplace_back(edge);
		}

		/// <summary>
		/// �C�e���[�^�̔z���ݒ�
		/// </summary>
		/// <param name="size"> �C�e���[�^�̔z��̃T�C�Y </param>
		void setIteratorAry(int32 size);

		/// <summary>
		/// �͈͓��̕������X�g���擾
		/// </summary>
		/// <param name="l"> �͈� �i�����ȕӂȂ�x���W , �����ȕӂȂ�y���W�j </param>
		/// <returns> �������X�g </returns>
		SubList getSubList(const std::pair<int32, int32>& region) const
		{
			return SubList(getItr(region.first), getItr(region.second));
		}

	private:

		/// <summary>
		/// �}�X���W����C�e���[�^�̎擾
		/// </summary>
		/// <param name="x"> �����ȕӂȂ�x���W , �����ȕӂȂ�y���W </param>
		/// <returns> �w��̃}�X���W���猩����ԏ��������W�̕� </returns>
		ConstItr getItr(int32 x) const;
	};
}