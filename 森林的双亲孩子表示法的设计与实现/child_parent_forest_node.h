#pragma once
#include"Assistance.h"
#include"node.h"

// ����˫����ʾɭ�ֽ����
template <class ElemType>
struct ChildParentForestNode
{
	// ���ݳ�Ա:
	string Tag;						//����Լ��Ƿ�Ϊ����
	ElemType data;					// ������
	Node<int>* childLkList;		    // ��������	
	int parent;						// ˫��λ����

// ���캯��:
	ChildParentForestNode();			// �޲����Ĺ��캯��
	ChildParentForestNode(ElemType item, int pt = -1, Node<int>* childlk = NULL);// ��֪������ֵ��˫��λ�ý����ṹ
};

// ����˫����ʾɭ�ֽ�����ʵ�ֲ���
template<class ElemType>
ChildParentForestNode<ElemType>::ChildParentForestNode()
// �������������˫����Ϊ-1�Ľ��
{	
	Tag = "UROOT";
	parent = -1;
	childLkList = NULL;
}

template<class ElemType>
ChildParentForestNode<ElemType>::ChildParentForestNode(ElemType item, int pt, Node<int>* childlk)
// �������������һ��������Ϊitem��˫����Ϊpt�Ľ��
{
	data = item;					// ����Ԫ��ֵ
	parent = pt;					// ˫��
	childLkList = childlk;
}