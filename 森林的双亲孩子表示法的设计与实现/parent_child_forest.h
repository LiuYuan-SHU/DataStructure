#pragma once
#include"Node.h"
#include"Assistance.h"
template<class ElemType>
class ParentChildForest
{
protected:
	// ɭ�ֵ����ݳ�Ա
	ParentChildForestNode<ElemType>* nodes;			                // �洢ɭ�ֽ��
	int maxSize;									// ����������� 
	int *root, num;									// ��ָ�뼰�����

	//	��������:
	void PreRootOrderHelp(int r, void (*Visit)(const ElemType&)) const;	  // �ȸ������
	void PostRootOrderHelp(int r, void (*Visit)(const ElemType&)) const;  //��������
	int HeightHelp(int r) const;					// ������rΪ���ĸ�
	int DegreeHelp(int r) const;					// ������rΪ�������Ķ�

public:
	ParentChildForest();							// �޲ι��캯��
	virtual ~ParentChildForest();					// ��������
	bool Empty() const;								// �ж�ɭ���Ƿ�Ϊ��
	Status GetElem(int cur, ElemType& e) const;		// ��e���ؽ��Ԫ��ֵ
	Status SetElem(int cur, const ElemType& e);		// ����cur��ֵ��Ϊe
	int NodeCount() const;
	int FirstChild(int cur) const;					// ���ؽ��cur�ĵ�һ������
	int RightSibling(int cur) const;				// ���ؽ��cur�����ֵ�
	int Parent(int cur) const;
	ParentChildForest(ElemType items[], int parents[], int r, int n, int size);
	void Show();
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
ParentChildForest<ElemType>::ParentChildForest(ElemType items[], int parents[], int r, int n, int size)
// �����������������Ԫ��Ϊitems[],��Ӧ���˫��Ϊparents[],�����λ��Ϊr,������Ϊn�� ɭ��
{	
	maxSize = size;													// ��������
	if (n > maxSize)
		throw Error("������̫��!");
	nodes = new ChildParentTreeNode<ElemType>[maxSize];				// ����洢�ռ�

	int i;
	for (i = 0; item[i] != NULL; i++) {            //ȫ����ŵ����������
		a[i + 1].data = item[i];
		a[i + 1].parent = parents[i];
		a[i + 1].firstChild = NULL;
	}
	a[0].parent = -1;
	num = Num;
	a[0].data = a[2].data;
	*root = a[0];
	for (i = 1; i <= num; i++) {            //����������ĺ��ӵĵ�����
		Child<ElemType>* p, * q;
		q = new Child<ElemType>(i, NULL); 
		if (a[a[i].parent].firstChild == NULL) {  //��һ������Ϊ�� ��ӵ�һ������
			a[a[i].parent].firstChild = q;
		}
		else {									  //��һ�����Ӳ�Ϊ�� ��Ӻ������ӵ�������		
			for (p = a[a[i].parent].firstChild; p->next != NULL; p = p->next) {}
			p->next = q;
		}
	}
	root->firstChild = a[0].firstChild;
}

template<class ElemType>
void ParentChildForest<ElemType>::Show()
{
	for (int i = 0; i <= num; i++) {
		cout << i;
		cout << "( " << a[i].data << ", " << a[i].parent << ", ";
		Child<ElemType>* p;
		if (a[i].firstChild == NULL) {
			cout << "^)" << endl;
		}
		else {
			p = a[i].firstChild;
			while (p) {
				cout << " )->( " << p->data << ", ";
				p = p->next;
			}
			cout << "^)" << endl;
		}
	}
}