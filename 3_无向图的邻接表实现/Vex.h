#ifndef VEX
#define VEX

/*
 * 注意，虽然设置模板参数的时候使用的是Person或Location
 * 但是vector中存储的是参数模板的指针
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

		// 返回大小
		size_t size() const { return _vexTable.size(); }

		// 支持使用下标访问符
		NodeType*& operator[](int index) { return _vexTable[index]; }
		// 插入节点
		void insertNode(NodeType* newNode) { _vexTable.push_back(newNode); }
		// 在数组中按名字寻找，并返回其下标
		// 如果没有找到，返回-1
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

