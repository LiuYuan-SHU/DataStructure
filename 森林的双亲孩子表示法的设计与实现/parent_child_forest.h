#pragma once
#include"Node.h"
#include"child_parent_forest_node.h"
#include"Assistance.h"
template<class ElemType>
class ParentChildForest
{
protected:
	// ɭ�ֵ����ݳ�Ա
	ChildParentForestNode<ElemType>* nodes;       //���ɭ�������н��
	int num_of_tree;                      //ɭ����������Ŀ
	int num;                             //ɭ���ܽ�����
	int maxSize;                       //ɭ�ֽ�������

	//	��������:
	void PreRootOrderHelp(int r, void (*Visit)(const ElemType&)) const;	  // �ȸ������
	void PostRootOrderHelp(int r, void (*Visit)(const ElemType&)) const;  //��������
	int HeightHelp(int r) const;					// ������rΪ�������Ķ�
	
public:
	ParentChildForest();							// �޲ι��캯��
	ParentChildForest(ElemType items[], int parents[],int n, int size= DEFAULT_SIZE);
	virtual ~ParentChildForest();					// ��������
	bool Empty() const;								// �ж�ɭ���Ƿ�Ϊ��
	Status GetElem(int cur, ElemType& e) const;		// ��e���ؽ��Ԫ��ֵ
	Status SetElem(int cur, const ElemType& e);		// ����cur��ֵ��Ϊe
	int NodeCount() const;
	int FirstChild(int cur) const;					// ���ؽ��cur�ĵ�һ������
	int RightSibling(int cur) const;				// ���ؽ��cur�����ֵ�
	int Parent(int cur) const;
	void Show();
	int getTreeNum();								//��ȡ���Ŀ���
};


template<class ElemType>
ParentChildForest<ElemType>::ParentChildForest()
{
	maxSize = DEFAULT_SIZE;								// �����������
	nodes = new ChildParentForestNode<ElemType>[maxSize];	// ����洢�ռ�
	//root = NULL;			
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

template <class ElemType>
Status ParentChildForest<ElemType>::GetElem(int cur, ElemType& e) const
// �����������e���ؽ��curԪ��ֵ,��������ڽ��cur,��������NOT_PRESENT,���򷵻�ENTRY_FOUND
{
	if (cur < 0 || cur >= num)		// �����ڽ��cur
		return NOT_PRESENT;			// ����NOT_PRESENT
	else {	                        // ���ڽ��cur
		e = nodes[cur].data;		// ��e����Ԫ��ֵ
		return ENTRY_FOUND;			// ����ENTRY_FOUND
	}
}

template <class ElemType>
Status ParentChildForest<ElemType>::SetElem(int cur, const ElemType& e)
// �����������������ڽ��cur,�򷵻�FAIL,���򷵻�SUCCESS,�������cur��ֵ����Ϊe
{
	if (cur < 0 || cur >= num)		// �����ڽ��cur
		return FAIL;				// ����FAIL
	else {	                    // ���ڽ��cur
		nodes[cur].data = e;		// �����cur��ֵ����Ϊe
		return SUCCESS;	  		    // ����SUCCESS
	}
}

template <class ElemType>
int ParentChildForest<ElemType>::NodeCount() const
// �������������ɭ�ֵĽ�����
{
	return num;
}

template <class ElemType>
int ParentChildForest<ElemType>::FirstChild(int cur) const
// �����������cur�޺���,�򷵻�-1,���򷵻������cur�ĵ�һ������,
{
	Node<int>* p;
	if (cur < 0 || cur >= num)
		return -1;						// ���cur������,����-1��ʾ�޺���

	if (nodes[cur].childLkList == NULL)	// �޺���
		return -1;
	else
		return nodes[cur].childLkList->data;	// ȡ����һ������
}

template <class ElemType>
int ParentChildForest<ElemType>::RightSibling(int cur) const
// ���������������cur�����ֵ�,�򷵻�-1,���򷵻�cur�����ֵ�
{
	if (cur < 0 || cur >= num)
		return -1;						// ���cur������,����-1��ʾ�޺���

	int pt = nodes[cur].parent;			// cur��˫��
	Node<int>* p = nodes[pt].childLkList;
	while (p != NULL && p->data != cur)
		p = p->next;
	if (p == NULL || p->next == NULL)
		return -1;				// �������ֵ�
	else
		return p->next->data;	// ��ʾ�����ֵ�
}

template <class ElemType>
int ParentChildForest<ElemType>::Parent(int cur) const
// ������������������cur��˫��
{
	if (cur < 0 || cur >= num)
		return -1;						// ���cur������,����-1��ʾ��˫��
	return nodes[cur].parent;
}


//�����޸�//
template <class ElemType>
ParentChildForest<ElemType>::ParentChildForest(ElemType items[], int parents[], int n, int size)
// �����������������Ԫ��Ϊitems[],��Ӧ���˫��Ϊparents[],�����λ��Ϊr,������Ϊn�� ɭ��
{	
	num_of_tree = 0;
	maxSize = size;													// ��������
	num = n;														// ������

	if (n > maxSize)
		throw Error("������̫��!");								    // �׳��쳣

	nodes = new ChildParentForestNode<ElemType>[maxSize];		    // ����洢�ռ�
	for (int pos = 0; pos < n; pos++)
	{	// ���ζԽ������Ԫ�ؼ�˫��λ�ý��и�ֵ
		nodes[pos].data = items[pos];								// ����Ԫ��ֵ
		nodes[pos].parent = parents[pos];							// ˫��λ��
		nodes[pos].childLkList = NULL;

		if (parents[pos] < 0) {			         //������ڵ���� �����������
			num_of_tree++;
			nodes[pos].Tag = "ROOT";		//����ɭ�ֽ������Ϊ����
		}
			  

		if (parents[pos] >= 0) {
			nodes[pos].Tag = "UROOT";		//����ɭ�ֽ������Ϊ������
			Node<int>* p, * q;
			q = new Node<int>(pos, NULL);
			if (nodes[parents[pos]].childLkList == NULL)            //�����һ�������ǿգ���ֱ�ӽ�q����Ϊ��һ������
				nodes[parents[pos]].childLkList = q; 
			else {
				for (p = nodes[parents[pos]].childLkList; p->next != NULL; p = p->next);  //Ѱ�ҵ�β��
				p->next = q;										//�����һ�����
			}
		}
	}

}

template<class ElemType>
void ParentChildForest<ElemType>::Show()  
{	
	std::cout <<"ɭ�������Ŀ���"<< num_of_tree << endl;
	for (int i = 0; i < num; i++) {
		std::cout << i;
		std::cout << nodes[i].Tag;
		std::cout << "( " << nodes[i].data << ", " << nodes[i].parent << ", ";
		Node<int>* p;
		if (nodes[i].childLkList == NULL) {
			std::cout << "^)" << endl;
		}
		else {
			p = nodes[i].childLkList;
			while (p) {
				std::cout << " )->( " << p->data << ", ";
				p = p->next;
			}
			std::cout << "^)" << endl;
		}
	}
}

template<class ElemType>
inline int ParentChildForest<ElemType>::getTreeNum()
{
	return num_of_tree;
}
