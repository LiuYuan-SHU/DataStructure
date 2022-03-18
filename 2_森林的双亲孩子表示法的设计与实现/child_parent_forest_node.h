#pragma once
#include"Assistance.h"
#include"node.h"

// 孩子双法表示森林结点类
template <class ElemType>
struct ChildParentForestNode
{
	// 数据成员:
	string Tag;						//标记自己是否为树根
	ElemType data;					// 数据域
	Node<int>* childLkList;		    // 孩子链表	
	int parent;						// 双亲位置域

// 构造函数:
	ChildParentForestNode();			// 无参数的构造函数
	ChildParentForestNode(ElemType item, int pt = -1, Node<int>* childlk = NULL);// 已知数据域值和双亲位置建立结构
};

// 孩子双法表示森林结点类的实现部分
template<class ElemType>
ChildParentForestNode<ElemType>::ChildParentForestNode()
// 操作结果：构造双亲域为-1的结点
{	
	Tag = "UROOT";
	parent = -1;
	childLkList = NULL;
}

template<class ElemType>
ChildParentForestNode<ElemType>::ChildParentForestNode(ElemType item, int pt, Node<int>* childlk)
// 操作结果：构造一个数据域为item和双亲域为pt的结点
{
	data = item;					// 数据元素值
	parent = pt;					// 双亲
	childLkList = childlk;
}