#ifndef VEX
#define VEX

/*
 * ע�⣬��Ȼ����ģ�������ʱ��ʹ�õ���Person��Location
 * ����vector�д洢���ǲ���ģ���ָ��
 */

#include "Arc.h"
#include "BaseNode.h"
#include <vector>
#include <algorithm>

using std::vector;
using std::find;

namespace liuyuan
{
	template <class NodeType>
	class Vex
	{
	private:
		vector<NodeType*> _vexTable;
	public:
		Vex() {}

		// ���ش�С
		size_t size() const { return _vexTable.size(); }

		// ֧��ʹ���±���ʷ�
		NodeType*& operator[](int index) { return _vexTable[index]; }
		// ����ڵ�
		void insertNode(NodeType* newNode) { _vexTable.push_back(newNode); }
		// �������а�����Ѱ�ң����������±�
		// ���û���ҵ�������-1
		int find_name(string name);
	};

	template<class Node>
	int Vex<Node>::find_name(string name)
	{
		int index = 0;
		for (; index < this->_vexTable.size(); index++)
		{
			if (this->_vexTable[index]->getName() == name)
			{
				return index;
			}
		}
		return -1;
	}
}

#endif // !VEX

