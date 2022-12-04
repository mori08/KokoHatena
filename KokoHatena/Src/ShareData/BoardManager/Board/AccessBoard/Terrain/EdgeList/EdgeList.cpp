#include "EdgeList.hpp"

namespace Kokoha
{
	void EdgeList::setIteratorAry(int32 size)
	{
		m_edgeList.sort();

		m_itrAry.resize(size);

		int32 index = 0;
		for (ConstItr itr = m_edgeList.begin(); itr != m_edgeList.end(); ++itr)
		{
			while (index < size && index < itr->first)
			{
				m_itrAry[index++] = itr;
			}
		}

		while (index < size)
		{
			m_itrAry[index++] = m_edgeList.end();
		}
	}

	EdgeList::ConstItr EdgeList::getItr(int32 x) const
	{
		if (x < 0) 
		{ 
			return m_edgeList.begin(); 
		}
		
		if (x >= m_itrAry.size())
		{
			return m_edgeList.end();
		}

		return m_itrAry[x];
	}
}