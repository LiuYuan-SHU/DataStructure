#pragma once
#include"Tools.h"
// 结点类
template <class ElemType>
struct ParentChildForestNode
{
	// 数据成员:
	ElemType data;				// 数据域
	Node<ElemType>* next;		// 指针域

// 构造函数:
	ParentChildForestNode();						// 无参数的构造函数
	ParentChildForestNode(ElemType item, Node<ElemType>* link = NULL);	// 已知数数据元素值和指针建立结构
};

// 结点类的实现部分
template<class ElemType>
ParentChildForestNode<ElemType>::ParentChildForestNode()
// 操作结果：构造指针域为空的结点
{
	next = NULL;
}

template<class ElemType>
ParentChildForestNode<ElemType>::ParentChildForestNode(ElemType item, Node<ElemType>* link)
// 操作结果：构造一个数据域为item和指针域为link的结点
{
	data = item;
	next = link;
}
