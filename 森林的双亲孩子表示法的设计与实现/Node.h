#pragma once
#include"Tools.h"
// �����
template <class ElemType>
struct ParentChildForestNode
{
	// ���ݳ�Ա:
	ElemType data;				// ������
	Node<ElemType>* next;		// ָ����

// ���캯��:
	ParentChildForestNode();						// �޲����Ĺ��캯��
	ParentChildForestNode(ElemType item, Node<ElemType>* link = NULL);	// ��֪������Ԫ��ֵ��ָ�뽨���ṹ
};

// ������ʵ�ֲ���
template<class ElemType>
ParentChildForestNode<ElemType>::ParentChildForestNode()
// �������������ָ����Ϊ�յĽ��
{
	next = NULL;
}

template<class ElemType>
ParentChildForestNode<ElemType>::ParentChildForestNode(ElemType item, Node<ElemType>* link)
// �������������һ��������Ϊitem��ָ����Ϊlink�Ľ��
{
	data = item;
	next = link;
}
