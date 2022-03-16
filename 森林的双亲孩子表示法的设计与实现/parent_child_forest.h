#pragma once
#include"Node.h"
#include"child_parent_forest_node.h"
#include"LinkQueue.h"
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
	int first_root;					   //ɭ�ֵ�һ�����ڵ�

	//	��������:
	void PreRootOrderHelp(int r) const;	  // �ȸ������
	void InorderRootOrderHelp(int r) const;	  // �и������
	void PostRootOrderHelp(int r) const;  //��������
	int HeightHelp(int r) const;					// ������rΪ�������Ķ�
	
public:
	ParentChildForest();							// �޲ι��캯��
	ParentChildForest(ElemType items[], int parents[],int n,int r, int size= DEFAULT_SIZE);
	virtual ~ParentChildForest();					// ��������
	bool Empty() const;								// �ж�ɭ���Ƿ�Ϊ��
	Status GetElem(int cur, ElemType& e) const;		// ��e���ؽ��Ԫ��ֵ
	Status SetElem(int cur, const ElemType& e);		// ����cur��ֵ��Ϊe
	int NodeCount() const;
	int FirstChild(int cur) const;					// ���ؽ��cur�ĵ�һ������   ���顿
	int RightSibling(int cur) const;				// ���ؽ��cur�����ֵ�	   ���顿
	int Parent(int cur) const;
	void Show();
	int getTreeNum();
	int getNum();
	ChildParentForestNode<ElemType> getNode(int i);
	//��ȡ���Ŀ���
	void PreRootOrder();							//ɭ�ֵ��ȸ�����
	void InorderRootOrder();							//ɭ�ֵ��ȸ�����
	void PostRootOrderOrder();							//ɭ�ֵĺ������
	int getLeafNum();								//��ȡҶ�ӽ������
	template<class T>
	friend ParentChildForest<T>* operator + (ParentChildForest<T> &t1, ParentChildForest<T> &t2); //ɭ�����
	Status append(ChildParentForestNode<ElemType> new_node);
	Status delnode(int pos);
	Status Modifyparent(int pos,int parent);                  //�޸�˫��

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
	if (pt < 0 || pt >= num) return -1;
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
ParentChildForest<ElemType>::ParentChildForest(ElemType items[], int parents[], int n,int r,int size)
// �����������������Ԫ��Ϊitems[],��Ӧ���˫��Ϊparents[],�����λ��Ϊr,������Ϊn�� ɭ��
{	
	num_of_tree = 0;
	maxSize = size;													// ��������
	num = n;														// ������
	first_root = r;													// ��¼ɭ�ֵĵ�һ���ĸ��ڵ�

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

template<class ElemType>
int ParentChildForest<ElemType>::getNum()
{	
	return num;
}

template<class ElemType>
ChildParentForestNode<ElemType> ParentChildForest<ElemType>::getNode(int i)
{
	return nodes[i];
}


template<class ElemType>
void ParentChildForest<ElemType>::PreRootOrderHelp(int r) const
{	
	if (r < 0 || r > num)
		return;
	std::cout << nodes[r].data;
	if (nodes[r].childLkList != NULL) PreRootOrderHelp(FirstChild(r));
	PreRootOrderHelp(RightSibling(r));
}

template<class ElemType>
void ParentChildForest<ElemType>::InorderRootOrderHelp(int r) const
{
	if (r < 0 || r > num)
		return;
	if (nodes[r].childLkList != NULL) InorderRootOrderHelp(FirstChild(r));
	std::cout << nodes[r].data;
	InorderRootOrderHelp(RightSibling(r));
}

template<class ElemType>
void ParentChildForest<ElemType>::PostRootOrderHelp(int r) const
{
	if (r < 0 || r > num)
		return;
	if (nodes[r].childLkList != NULL) PostRootOrderHelp(FirstChild(r));
	PostRootOrderHelp(RightSibling(r));
	std::cout << nodes[r].data;
}






template<class ElemType>
void ParentChildForest<ElemType>::PreRootOrder()
{	
	LinkQueue<int> L;
	for (int i = 0; i < num; i++) {
		if(nodes[i].Tag=="ROOT")
		L.EnQueue(i);
	}
	int treeroot;
	while (!L.IsEmpty()) {
		L.DelQueue(treeroot);
		PreRootOrderHelp(treeroot);
	}
}

template<class ElemType>
inline void ParentChildForest<ElemType>::InorderRootOrder()
{
	LinkQueue<int> L;
	for (int i = 0; i < num; i++) {
		if (nodes[i].Tag == "ROOT")
			L.EnQueue(i);
	}
	int treeroot;
	while (!L.IsEmpty()) {
		L.DelQueue(treeroot);
		InorderRootOrderHelp(treeroot);
	}
}

template<class ElemType>
void ParentChildForest<ElemType>::PostRootOrderOrder()
{
	LinkQueue<int> L;
	for (int i = 0; i < num; i++) {
		if (nodes[i].Tag == "ROOT")
			L.EnQueue(i);
	}
	int treeroot;
	while (!L.IsEmpty()) {
		L.DelQueue(treeroot);
		PostRootOrderHelp(treeroot);
	}
}

template<class ElemType>
int ParentChildForest<ElemType>::getLeafNum()
{	
	int sum=0;
	for (int i = 0; i < num; i++) {
		if (nodes[i].childLkList == NULL && nodes[i].Tag!="ROOT") sum++;
	}
	return sum;
}

template<class ElemType>
Status ParentChildForest<ElemType>::append(ChildParentForestNode<ElemType> new_node)
{
	//���ӽ����nodes��
	ChildParentForestNode<ElemType>* temp = new ChildParentForestNode<ElemType>[maxSize + 1];
	for (int i = 0; i < num; i++) {
		temp[i] = nodes[i];
	}
	temp[num] = new_node;
	temp[num].Tag = "UROOT";
	nodes = temp;
	if (new_node.parent >= 0 && new_node.parent < maxSize) {
		int pn = new_node.parent;
		Node<int>* p ;
		Node<int>* q=new Node<int>(num,NULL) ;
		for (p = nodes[pn].childLkList; p->next != NULL; p = p->next);
		p->next = q;
		nodes[pn].Tag = "UROOT";
	}
	num++;
	return SUCCESS;
}

template<class ElemType>
Status ParentChildForest<ElemType>::delnode(int pos)
{	
	//�����
	ChildParentForestNode<ElemType>* temp = new ChildParentForestNode<ElemType>[maxSize];
	if (num-1 == pos) { num--; return SUCCESS; }
	nodes[pos] = nodes[num];//�����е�pos����ɾ�� ͨ��˫��  �����е�num���ӻ���pos

	nodes[pos]= nodes[num-1];						
	Node<int>* p;
	Node<int>* q;
	int pn = nodes[pos].parent;
	int pnum = nodes[num-1].parent;
	if (pn>=0&&pn<num) 
	for (p = nodes[pn].childLkList,q=p; p!= NULL; q = p,p = p->next)
	{	
		if (p->data == pos) {
			q->next = p->next;   //������pos �ĺ���ɾ��
		}
	}

	if (nodes[pnum].childLkList != NULL)
	for (p = nodes[pnum].childLkList; p!= NULL;p = p->next)
	{
		if (p!=NULL && p->data == num-1) {
			p->data= pos;   //������num �ĺ����޸�Ϊpos
		}
	}
	num--;
	return SUCCESS;
}

template<class ElemType>
inline Status ParentChildForest<ElemType>::Modifyparent(int pos,int Parent)
{	
	Node<int>* p;
	Node<int>* q;
	if (pos<0 || pos>num) throw Error("��Χ����");
 	if (nodes[pos].parent >=0) {
		for (p = nodes[nodes[pos].parent].childLkList,q=p; p != NULL; q=p,p = p->next) {  //���ٺ���
			if (p->data == pos) {
				q->next = p->next;
			}
		}
	}
	nodes[pos].parent = Parent;
	Node<int>* new_node = new Node<int>(pos, NULL);       //���Ӻ���
	if (nodes[Parent].childLkList == NULL) nodes[Parent].childLkList = new_node;
	else {
		for (p = nodes[Parent].childLkList; p->next != NULL; p = p->next);
		p->next = new_node;
	}
	
	return SUCCESS;
}


template<class T>
ParentChildForest<T>* operator+(ParentChildForest<T> &t1, ParentChildForest<T> &t2)
{	
	ParentChildForest<T> *result=new ParentChildForest<T> ;
	for (int i = 0; i < t1.getNum(); i++) {
		result->append(t1.getNode(i));
	}
	for (int i = 0; i < t2.getNum(); i++) {
		result->append(t2.getNode(i));
	}
	return result;
}
