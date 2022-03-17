#ifndef __CHILD_SIBLING_TREE_H__
#define __CHILD_SIBLING_TREE_H__

#include "LinkQueue.h"						// ������
#include "child_sibling_tree_node.h"		// �����ֵܱ�ʾ�������
#include<vector>

// �����ֵܱ�ʾ����
template <class ElemType>
class ChildSiblingTree
{
protected:
//  �������ݳ�Ա:
	ChildSiblingTreeNode<ElemType> *root;			// ��ָ�� 

//	��������:
	void Destroy(ChildSiblingTreeNode<ElemType> * &r);		// ������rΪ������
	void PreRootOrder(ChildSiblingTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const;
	//void PreRootOrderWithStack(ChildSiblingTreeNode<ElemType>* r, void(*Visit)(const ElemType&)) const;

		// �ȸ�������rΪ������ 
	void PostRootOrder(ChildSiblingTreeNode<ElemType> *r, void (*Visit)(const ElemType &)) const;
		// ���������rΪ������(�������油���������룩 
	int NodeCount(ChildSiblingTreeNode<ElemType> *r) const;	// ����rΪ�������Ľ�����
	int Height(ChildSiblingTreeNode<ElemType> *r) const;	// ����rΪ�������ĸ�(�������油���������룩 
	int BHeight(ChildSiblingTreeNode<ElemType> *r) const;	// ����rλ���Ķ������ĸ� 
	int Degree(ChildSiblingTreeNode<ElemType> *r) const;	// ����rΪ�������Ķ�
	ChildSiblingTreeNode<ElemType> *Parent(ChildSiblingTreeNode<ElemType> *r, 
		const ChildSiblingTreeNode<ElemType> *cur) const;	//  ��cur��˫��
	ChildSiblingTreeNode<ElemType> *CopyTree(ChildSiblingTreeNode<ElemType> *copy);	
		// ������
	//ChildSiblingTreeNode<ElemType> *CreateTreeGhelp(vector<ElemType> items,vector<ElemType> parents, int r, int n);
		// ��������Ԫ��Ϊitems[],��Ӧ���˫��Ϊparents[],�����λ��Ϊr,������Ϊn�������� �����ĸ�

public:
//  �����ֵܱ�ʾ���෽��������:
	ChildSiblingTree();									// �޲����Ĺ��캯��
	virtual ~ChildSiblingTree();						// ��������
	ChildSiblingTreeNode<ElemType> * GetRoot() const;	//  �����ĸ�
	bool IsEmpty() const;								// �ж����Ƿ�Ϊ��
	Status GetElem(ChildSiblingTreeNode<ElemType> *cur, ElemType &e) const;
		// ��e ����Ԫ��ֵ
	Status SetElem(ChildSiblingTreeNode<ElemType> *cur, const ElemType &e);
		// ����cur��ֵ��Ϊe
	void PreRootOrder(void (*Visit)(const ElemType &)) const;		// �����ȸ������
	//void PreRootOrderWithStack(void (*Visit)(const ElemType &)) const;		// �����ȸ������
	void PostRootOrder(void (*Visit)(const ElemType &)) const;		// ���ĺ�������
	//void LevelOrder(void (*Visit)(const ElemType &)) const;			// ���Ĳ�α���
	int NodeCount() const;								            // �����Ľ�����
	int NodeDegree(ChildSiblingTreeNode<ElemType> *cur) const;	    // ����cur�Ķ�
	int Degree() const;									            // �����Ķ�
	ChildSiblingTreeNode<ElemType> *FirstChild(ChildSiblingTreeNode<ElemType> *cur) const;	
		// �������cur�ĵ�һ������
	ChildSiblingTreeNode<ElemType> *NextSibling(ChildSiblingTreeNode<ElemType> *cur) const;				
		// �������cur����һ���ֵ�
	ChildSiblingTreeNode<ElemType> *Parent(ChildSiblingTreeNode<ElemType> *cur) const;
		// ����cur��˫��
	Status InsertChild(ChildSiblingTreeNode<ElemType> *cur, int i, const ElemType &e);	
		// ������Ԫ��e����Ϊcur�ĵ�i������
	Status DeleteChild(ChildSiblingTreeNode<ElemType> *cur, int i);// ɾ��cur�ĵ�i��������
	int	Height() const;									//  �����ĸ�
	int	BHeight() const;									//  �����ĸ�
	ChildSiblingTree(const ElemType &e);				// ����������Ԫ��eΪ������
	ChildSiblingTree(const ChildSiblingTree<ElemType> &copy);	// ���ƹ��캯��


	ChildSiblingTreeNode<ElemType>* CreateTreeGhelp(vector<ElemType>& items, vector<ElemType>& parents, int r, int n);

	ChildSiblingTree(vector<ElemType> elems, vector<ElemType> parents, vector<ElemType> rootpos, int n);
		// ��������Ԫ��Ϊitems[],��Ӧ���˫��Ϊparents[],�����λ��Ϊr,������Ϊn����


	ChildSiblingTree(ChildSiblingTreeNode<ElemType> *r);// ������rΪ������
	ChildSiblingTree<ElemType> &operator=(const ChildSiblingTree<ElemType>& copy);	
		// ���ظ�ֵ����
};

template <class ElemType>
void DisplayTWithConcaveShape(const ChildSiblingTree<ElemType> &t, ChildSiblingTreeNode<ElemType> *r, int level);
	// �������ʾ����ʾ����levelΪ�������������Ĳ����Ϊ1
template <class ElemType>
void DisplayTWithConcaveShape(const ChildSiblingTree<ElemType> &t);
	// �������ʾ����ʾ��

// �����ֵܱ�ʾ�����ʵ�ֲ���

template <class ElemType>
ChildSiblingTree<ElemType>::ChildSiblingTree()
// �������������һ������
{
	root = NULL;					// ��ʾ��Ϊ��
}

template <class ElemType>
void ChildSiblingTree<ElemType>::Destroy(ChildSiblingTreeNode<ElemType> * &r)
// ���������������rΪ������
{
    ChildSiblingTreeNode<ElemType> *p;
	if (r != NULL)	{
		for (p = FirstChild(r); p != NULL; p = NextSibling(p))
			Destroy(p);		// ��������
		delete r;				// ���ٸ����
		r = NULL;
	}
}

template <class ElemType>
ChildSiblingTree<ElemType>::~ChildSiblingTree()
// ���������������--���캯��
{
	Destroy(root);
}

template <class ElemType>
ChildSiblingTreeNode<ElemType> *ChildSiblingTree<ElemType>::GetRoot() const
// ��������� �����ĸ�
{
	return root;
}

template <class ElemType>
bool ChildSiblingTree<ElemType>::IsEmpty() const
// ����������ж����Ƿ�Ϊ��
{
	return root == NULL;
}

template <class ElemType>
Status ChildSiblingTree<ElemType>::GetElem(ChildSiblingTreeNode<ElemType> *cur, ElemType &e) const
// �����������e ����curԪ��ֵ,��������ڽ��cur,���� ��NOT_PRESENT,���� ��ENTRY_FOUND
{
	if (cur == NULL)
		return NOT_PRESENT;	
	else	{
		e = cur->data;			// ��e ��Ԫ��ֵ
		return ENTRY_FOUND;		//  ��ENTRY_FOUND
	}
}

template <class ElemType>
Status ChildSiblingTree<ElemType>::SetElem(ChildSiblingTreeNode<ElemType> *cur, const ElemType &e)
// �����������������ڽ��cur,�� ��FAIL,���� ��SUCCESS,�������cur��ֵ����Ϊe
{
	if (cur == NULL)	
		return FAIL;
	else	{
		cur->data = e;			// �����cur��ֵ����Ϊe
		return SUCCESS;			//  ��SUCCESS
	}
}

template <class ElemType>
void ChildSiblingTree<ElemType>::PreRootOrder(ChildSiblingTreeNode<ElemType> *r, 
	void (*Visit)(const ElemType &)) const
// ������������ȸ������ζ���rΪ��������ÿ��Ԫ�ص��ú���(*visit)���� 
{
    ChildSiblingTreeNode<ElemType> *p;
	if (r != NULL)	{	
		(*Visit)(r->data);			// ���ʸ����
		for (p = FirstChild(r); p != NULL;	p = NextSibling(p))
			PreRootOrder(p, Visit);// �����ȸ������������ÿ������
	}
}

//template <class ElemType>
//void ChildSiblingTree<ElemType>::PreRootOrderWithStack(ChildSiblingTreeNode<ElemType>* r,
//	void (*Visit)(const ElemType&)) const
//	// ������������ȸ������ζ���rΪ��������ÿ��Ԫ�ص��ú���(*visit)���� 
//{
//	ChildSiblingTreeNode<ElemType>* p=root;
//	ChildSiblingTreeNode<ElemType>* q=p->nextSibling;
//	SeqStack<ChildSiblingTreeNode<ElemType>> s;
//	while (p!=NULL) {
//			(*Visit)(p->data);
//			q = p->nextSibling;
//			if (q != NULL) { s.Push(*q); }
//		if (p->firstChild != NULL) {
//			p = p->firstChild;
//		}
//		else {
//			if (!s.IsEmpty()) {
//				ChildSiblingTreeNode<ElemType> Temp;
//				s.Pop(Temp);
//				p = &Temp;
//			}
//			else break;
//		}
//	}
//}

template <class ElemType>
void ChildSiblingTree<ElemType>::PreRootOrder(void (*Visit)(const ElemType &)) const
// ������������ȸ������ζ�����ÿ��Ԫ�ص��ú���(*visit)���� 
{
	PreRootOrder(GetRoot(), Visit);
}

//template<class ElemType>
//void ChildSiblingTree<ElemType>::PreRootOrderWithStack(void(*Visit)(const ElemType&)) const
//{
//	PreRootOrderWithStack(GetRoot(), Visit);
//}



//template <class ElemType>
//void ChildSiblingTree<ElemType>::LevelOrder(void (*Visit)(const ElemType &)) const
//// �����������α�����
//{
//	LinkQueue<ChildSiblingTreeNode<ElemType> *> q;	// ������ж��� 
//	ChildSiblingTreeNode<ElemType> *cur, *p;
//	
//	if (root != NULL) q.EnQueue(root);			   // ������ǿ�,������ָ�������
//	while (!q.IsEmpty())	{
//		q.DelQueue(cur);						   //  ��ͷ������Ϊ��ǰ���cur 
//		(*Visit)(cur->data);					   // ���ʵ�ǰ���cur
//		for (p = FirstChild(cur); p != NULL;  p = NextSibling(p))
//			q.EnQueue(p);					       // ���ν�cur�ĺ��ӽ��ָ�������
//	}
//}

template <class ElemType>
int ChildSiblingTree<ElemType>::NodeCount(ChildSiblingTreeNode<ElemType> *r) const
// ��������� ����rΪ�������Ľ�����
{
    ChildSiblingTreeNode<ElemType> *p;
	if (r == NULL) return 0;			// ����������Ϊ0
	else	{
		int subTreeNodeCountSum = 0;
		for (p = FirstChild(r); p != NULL;  p = NextSibling(p))
			subTreeNodeCountSum += NodeCount(p);// �ۼ�����������
		return 1 + subTreeNodeCountSum;	   // �ǿ�������Ϊ�����Ľ�����֮���ټ�1
	}
}

template <class ElemType>
int ChildSiblingTree<ElemType>::NodeCount() const
// ��������� �����Ľ�����
{
	return NodeCount(root);	
}

template <class ElemType>
int ChildSiblingTree<ElemType>::NodeDegree(ChildSiblingTreeNode<ElemType> *cur) const
// ��������� ����cur�Ķ�
{
    ChildSiblingTreeNode<ElemType> *p;
	int count = 0;
	for (p = FirstChild(cur); p != NULL;    p = NextSibling(p))
		count++;					// �Ժ��Ӹ������м���
	return count;
}

template <class ElemType>
int ChildSiblingTree<ElemType>::Degree(ChildSiblingTreeNode<ElemType> *r) const
// ��������� ����rΪ�������Ķ�
{
    ChildSiblingTreeNode<ElemType> *p;
	int d = 0;
	int maxSubTreeDegree = 0;	// �����ȵ����� 
	for (p = FirstChild(r); p != NULL;  p = NextSibling(p))	{	
		d++;					// �Ժ��Ӹ������м���
		int subTreeDegree = Degree(p);	//  ����pΪ����������
		maxSubTreeDegree = (maxSubTreeDegree < subTreeDegree) ? subTreeDegree : maxSubTreeDegree;
			// �����������ֵ
	}
	return (d < maxSubTreeDegree) ? maxSubTreeDegree : d;
}

template <class ElemType>
int ChildSiblingTree<ElemType>::Degree() const
// ��������� �����Ķ�
{
	return Degree(root);
}

template <class ElemType>
ChildSiblingTreeNode<ElemType> *ChildSiblingTree<ElemType>::FirstChild(ChildSiblingTreeNode<ElemType> *cur) const
// �����������cur�޺���,�򷵻�NULL,���򷵻������cur�ĵ�һ������,
{
	if (cur == NULL)
		return NULL;				// �ս���޺���		
	else
		return cur->firstChild;		// firstChildΪ��һ������
}

template <class ElemType>
ChildSiblingTreeNode<ElemType> *ChildSiblingTree<ElemType>::NextSibling(ChildSiblingTreeNode<ElemType> *cur) const
// ���������������curΪ�ջ�û����һ���ֵ�,�򷵻�NULL,���򷵻�cur����һ���ֵ�
{
	if (cur == NULL)
		return NULL;				// �ս�����ֵ�
	else
		return cur->nextSibling;	// nextSiblingΪ��һ���ֵ�
}

template <class ElemType>
ChildSiblingTreeNode<ElemType> *ChildSiblingTree<ElemType>::Parent(ChildSiblingTreeNode<ElemType> *r, 
	const ChildSiblingTreeNode<ElemType> *cur) const
// �������������rΪ������, ���cur��˫��
{
	if (r == NULL) return NULL;				// �ն�����
	
	ChildSiblingTreeNode<ElemType> *p;		// ���� 
	for (p = FirstChild(r); p != NULL;	p = NextSibling(p))
		if (p == cur) return r;				// cur��r�ĺ���
	
	for (p = FirstChild(r); p != NULL;	p = NextSibling(p))	{
		ChildSiblingTreeNode<ElemType> *q;
		q = Parent(p, cur);			        // ����������cur��˫��	
		if (q != NULL) return q;			// ˫����������
	}
	
	return NULL;							// δ�ҵ�˫��
}



template <class ElemType>
ChildSiblingTreeNode<ElemType> *ChildSiblingTree<ElemType>::Parent(ChildSiblingTreeNode<ElemType> *cur) const
// �������������cur��˫��
{
	return Parent(root, cur);
}

template <class ElemType>
Status ChildSiblingTree<ElemType>::InsertChild(ChildSiblingTreeNode<ElemType> *cur, int i, const ElemType &e)
// ���������������Ԫ�ز���Ϊcur�ĵ�i������,�������ɹ�,�򷵻�SUCCESS,���򷵻�FAIL
{
	if (cur == NULL) return FAIL;
	if (i < 1 || i > NodeDegree(cur) + 1) return FAIL;

	ChildSiblingTreeNode<ElemType> *newNode = new ChildSiblingTreeNode<ElemType>(e);
 	    // �����½��ռ� 
	if (i == 1)	{
        newNode->nextSibling = cur->firstChild; 
		cur->firstChild = newNode;				// newNode����Ϊcur�ĵ�һ������ 
	}	
	else {
	    ChildSiblingTreeNode<ElemType> *p = FirstChild(cur);// ȡcur�ĺ��� 
		for (int k = 1; k < i - 1; k++)
		  p = NextSibling(p);       // �����λ�õ�ǰһ���ֵ�p 
        newNode->nextSibling = p->nextSibling; 
	    p->nextSibling = newNode;
	}    
	return SUCCESS;
}

template <class ElemType>
Status ChildSiblingTree<ElemType>::DeleteChild(ChildSiblingTreeNode<ElemType> *cur, int i)
// ���������ɾ��cur�ĵ�i��������,���ɾ���ɹ�,�� ��SUCCESS,���� ��FAIL
{
    ChildSiblingTreeNode<ElemType> *p, *q;

	if (i < 0 && i > NodeDegree(cur)) return FAIL;	// ����λ�ò���ȷ������ʧ��
	
	if (i == 1)	{
		p = cur->firstChild;
		cur->firstChild = p->nextSibling;		// ɾ��cur�ĵ�1������
	}
	else	{
		q = FirstChild(cur);
		for (int n = 1; n < i - 1; n++)
            q = NextSibling(q);			// ����cur�ĵ�i - 1������
		p = q->nextSibling;	
		q->nextSibling = p->nextSibling;		// ɾ����i��������
	}
	Destroy(p);							        // ���ٵ�i������
	return SUCCESS;								// ���ز����ɹ�
}

template <class ElemType>
ChildSiblingTree<ElemType>::ChildSiblingTree(const ElemType &e)
// �������������������Ԫ��eΪ������
{
	root = new ChildSiblingTreeNode<ElemType>(e);	// ���ɸ����
}

template <class ElemType>
ChildSiblingTreeNode<ElemType> *ChildSiblingTree<ElemType>::CopyTree(ChildSiblingTreeNode<ElemType> *troot)
// �������������trootΪ���������Ƴ��µ���, �������ĸ�
{
	if (troot == NULL)
		return NULL;					// �ն�������Ϊ��	
	else	{	// ���Ʒǿն�����
		ChildSiblingTreeNode<ElemType> *r = new ChildSiblingTreeNode<ElemType>(troot->data);	// ���Ƹ����
		ChildSiblingTreeNode<ElemType> *subTreeRoot,*p;
		ChildSiblingTreeNode<ElemType>* cur = new ChildSiblingTreeNode<ElemType>;
		
		for (p = FirstChild(troot); p != NULL;	p = NextSibling(p)){	// ��������
			subTreeRoot = CopyTree(p);	// ��������
			if (r->firstChild == NULL)		{
				r->firstChild = subTreeRoot;	// subTreeRootΪ�׺���	
				cur = subTreeRoot;				// cur���¸��Ƶ������ĸ�
			}
			else	{
				cur->nextSibling = subTreeRoot;// subTreeRootΪ��һ���ֵ�
				cur = subTreeRoot;				// cur���¸��Ƶ������ĸ�
			}
		}
		return r;
	}
}

template <class ElemType>
ChildSiblingTree<ElemType>::ChildSiblingTree(const ChildSiblingTree<ElemType> &t)
// �������������֪�����������������ƹ��캯��
{
	root = CopyTree(t.GetRoot());
}
  
template <class ElemType>
ChildSiblingTreeNode<ElemType> *ChildSiblingTree<ElemType>::CreateTreeGhelp(vector<ElemType> &items, vector<ElemType> &parents, int r, int n)
// �����������������Ԫ��Ϊitems[],��Ӧ���˫��Ϊparents[],�����λ��Ϊr,������Ϊn���������������ĸ�
{
	if (r >= 0 && r < n){
		ChildSiblingTreeNode<ElemType> *rt = new ChildSiblingTreeNode<ElemType>(items[r]);	// ���Ƹ����
		ChildSiblingTreeNode<ElemType> *subTreeRoot;
		ChildSiblingTreeNode<ElemType>* cur = new ChildSiblingTreeNode<ElemType>;
		for (int i = 0; i < n; i++)	{	// ����r�ĺ���
			if (parents[i] == r)	{	// ������posΪ��������
				subTreeRoot = CreateTreeGhelp(items, parents, i, n);
				if (rt->firstChild == NULL)	{	// subTreeRootΪrt��һ�������ĸ�
					rt->firstChild = subTreeRoot;	
					cur = subTreeRoot;	        // cur���¸��Ƶ������ĸ�
				}
				else{	               // subTreeRootΪcur����һ���ֵ�
					cur->nextSibling = subTreeRoot;
					cur = subTreeRoot;
				}
			}
		}
		return rt;
	}
	else return NULL;									// r�Ƿ�����������
}

template<class ElemType>
ChildSiblingTree<ElemType>::ChildSiblingTree(vector<ElemType> elems, vector<ElemType> parents, vector<ElemType> rootpos, int n)
{	
	ChildSiblingTreeNode<ElemType>* p=new ChildSiblingTreeNode<ElemType>;  //��ɭ������Ϊһ����
	for (int i = 0; i < rootpos.size(); i++) {
		if (root == NULL) {
			root = CreateTreeGhelp(elems, parents, rootpos[i], n);
			p = root;
		}
		else {
			p->nextSibling = CreateTreeGhelp(elems, parents, rootpos[i], n);
			p = p->nextSibling;
		}
	}
}

template <class ElemType>
ChildSiblingTree<ElemType>::ChildSiblingTree(ChildSiblingTreeNode<ElemType> *r)
// ���������������rΪ������
{
	root = r;
}


template <class ElemType>
ChildSiblingTree<ElemType> &ChildSiblingTree<ElemType>::operator=(const ChildSiblingTree<ElemType> &copy)
// �������������֪��copy���Ƶ���ǰ��--��ֵ��������
{
	if (&copy != this)	{
		Destroy(root);						// ������
		root = CopyTree(copy.GetRoot());
	}
	return *this;
}

template <class ElemType>
void DisplayTWithConcaveShape(const ChildSiblingTree<ElemType> &t, 
	ChildSiblingTreeNode<ElemType> *r, int level)
// ����������������ʾ����ʾ����levelΪ�������������Ĳ����Ϊ1
{
    ChildSiblingTreeNode<ElemType> *p;
	if (r != NULL)	{
		cout<<endl;									//��ʾ����	
		for(int i = 0; i < level - 1; i++)
			cout<<"   ";								//ȷ���ڵ�level����ʾ���
		ElemType e;
		t.GetElem(r, e);							// ȡ�����r��Ԫ��ֵ
		cout << e;									// ��ʾ���Ԫ��ֵ
		for (p = t.FirstChild(r); p != NULL;	p = t.NextSibling(p))
			DisplayTWithConcaveShape(t, p, level + 1);// ������ʾ��������
	}
}

template <class ElemType>
void DisplayTWithConcaveShape(const ChildSiblingTree<ElemType> &t)
// ����������������ʾ����ʾ��
{
	DisplayTWithConcaveShape(t, t.GetRoot(), 1);// ���ø�������ʵ�ְ������ʾ����ʾ��
	cout << endl;									// ����
}

template <class ElemType>
void ChildSiblingTree<ElemType>::PostRootOrder(ChildSiblingTreeNode<ElemType> *r,
    void (*Visit)(const ElemType &)) const
// �������������������ζ���rΪ��������ÿ��Ԫ�ص��ú���(*visit)����
{
/////////////////////////////������������//////////////////////////
	ChildSiblingTreeNode<ElemType>* p;
	if (r != NULL) {
		for (p = FirstChild(r); p != NULL; p = NextSibling(p))
			PostRootOrder(p, Visit);// �����ȸ������������ÿ������
			(*Visit)(r->data);			// ���ʸ����
	}
}

template <class ElemType>
void ChildSiblingTree<ElemType>::PostRootOrder(void (*Visit)(const ElemType &)) const
// �������������������ζ�����ÿ��Ԫ�ص��ú���(*visit)����
{
	PostRootOrder(GetRoot(), Visit);
}

template <class ElemType>
int ChildSiblingTree<ElemType>::Height(ChildSiblingTreeNode<ElemType> *r) const
// ��������� ����rΪ�������ĸ�
{
/////////////////////////////������������//////////////////////////
	if (r == NULL)
		return 0;
	else {
		int DownHeight, Sibling;
		DownHeight = Height(r->firstChild);
		Sibling = Height(r->nextSibling);
		if (DownHeight >= Sibling) return DownHeight + 1;
		else return Sibling;
	}

}

template <class ElemType>
int ChildSiblingTree<ElemType>::BHeight(ChildSiblingTreeNode<ElemType>* r) const
// ��������� ����rΪ����ת����Ķ������ĸ�
{

	if (r == NULL)
		return 0;
	else {
		int lHeight, rHeight;
		lHeight = BHeight(r->firstChild);
		rHeight = BHeight(r->nextSibling);
		return (lHeight > rHeight ? lHeight : rHeight) + 1;
	}

}


template <class ElemType>
int ChildSiblingTree<ElemType>::Height() const
// ��������� �����ĸ�
{
	return Height(root);
}

template <class ElemType>
int ChildSiblingTree<ElemType>::BHeight() const
// ��������� �����ĸ�
{
	return BHeight(root);
}



#endif
