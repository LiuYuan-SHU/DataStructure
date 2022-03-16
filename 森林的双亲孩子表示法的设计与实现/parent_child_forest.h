#pragma once
#include"Node.h"
#include"Assistance.h"
template<class ElemType>
class ParentChildForest
{
protected:
	// ɭ�ֵ����ݳ�Ա
	ChildParentTreeNode<ElemType>* nodes;			// �洢ɭ�ֽ��
	int maxSize;									// ����������� 
	int *root, num;									// ����λ�ü������

	//	��������:
	void PreRootOrderHelp(int r, void (*Visit)(const ElemType&)) const;	// �ȸ������
	void PostRootOrderHelp(int r, void (*Visit)(const ElemType&)) const;	// ��������
	int HeightHelp(int r) const;					// ������rΪ���ĸ�
	int DegreeHelp(int r) const;					// ������rΪ�������Ķ�

public:
	ParentChildForest();							//�޲ι��캯��
	virtual ~ParentChildForest();						// ��������
	bool Empty() const;								//�ж�ɭ���Ƿ�Ϊ��
};

template<class ElemType>
ParentChildForest<ElemType>::ParentChildForest()
{
	maxSize = DEFAULT_SIZE;								// �����������
	nodes = new ChildParentTreeNode<ElemType>[maxSize];	// ����洢�ռ�
	root = -1;											// ��ʾ�����ڸ�
	num = 0;											// ��ɭ�Ľ�����Ϊ0
}

template <class ElemType>
ParentChildForest<ElemType>::~ParentChildForest()
// ����������ͷŴ洢�ռ�
{
	Node<int>* p;
	for (int n = 0; n < num; n++) {
		p = nodes[n].childLkList;
		while (p != NULL) {
			nodes[n].childLkList = p->next;
			delete p;
			p = nodes[n].childLkList;
		}
	}
	delete[]nodes;										// �ͷŴ洢�ռ�
}

template <class ElemType>
bool ParentChildForest<ElemType>::Empty() const
// ����������ж�ɭ���Ƿ�Ϊ��
{
	return num == 0;
}