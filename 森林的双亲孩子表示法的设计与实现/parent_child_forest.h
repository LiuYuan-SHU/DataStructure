#pragma once
#include"Node.h"
#include"Assistance.h"
template<class ElemType>
class ParentChildForest
{
protected:
	// ɭ�ֵ����ݳ�Ա
	ChildParentTreeNode<ElemType>* nodes;			// �洢�����
	int maxSize;									// ����������� 
	int root, num;									// ����λ�ü������

	//	��������:
	void PreRootOrderHelp(int r, void (*Visit)(const ElemType&)) const;	// �ȸ������
	void PostRootOrderHelp(int r, void (*Visit)(const ElemType&)) const;	// ��������
	int HeightHelp(int r) const;					// ������rΪ���ĸ�
	int DegreeHelp(int r) const;					// ������rΪ�������Ķ�

public:
	ParentChildForest();							//�޲ι��캯��
	virtual ~ChildParentTree();						// ��������
};