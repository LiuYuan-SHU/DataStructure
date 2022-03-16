#pragma once
#include"Node.h"
#include"Assistance.h"
template<class ElemType>
class ParentChildForest
{
protected:
	// 森林的数据成员
	ChildParentTreeNode<ElemType>* nodes;			// 存储森林结点
	int maxSize;									// 树结点最大个数 
	int *root, num;									// 根的位置及结点数

	//	辅助函数:
	void PreRootOrderHelp(int r, void (*Visit)(const ElemType&)) const;	  // 先根序遍历
	void PostRootOrderHelp(int r, void (*Visit)(const ElemType&)) const;  //后根序遍历
	int HeightHelp(int r) const;					// 返回以r为根的高
	int DegreeHelp(int r) const;					// 返回以r为根的树的度

public:
	ParentChildForest();							// 无参构造函数
	virtual ~ParentChildForest();					// 析构函数
	bool Empty() const;								// 判断森林是否为空
	Status GetElem(int cur, ElemType& e) const;		// 用e返回结点元素值
	Status SetElem(int cur, const ElemType& e);		// 将结cur的值置为e
	int NodeCount() const;
	int FirstChild(int cur) const;					// 返回结点cur的第一个孩子
	int RightSibling(int cur) const;				// 返回结点cur的右兄弟
	int Parent(int cur) const;
};

template<class ElemType>
ParentChildForest<ElemType>::ParentChildForest()
{
	maxSize = DEFAULT_SIZE;								// 树结点最大个数
	nodes = new ChildParentTreeNode<ElemType>[maxSize];	// 分配存储空间
	root = -1;											// 表示不存在根
	num = 0;											// 空森的结点个数为0
}

template <class ElemType>
ParentChildForest<ElemType>::~ParentChildForest()
// 操作结果：释放存储空间
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
	delete[]nodes;										// 释放存储空间
}

template <class ElemType>
bool ParentChildForest<ElemType>::Empty() const
// 操作结果：判断森林是否为空
{
	return num == 0;
}

template <class ElemType>
Status ParentChildForest<ElemType>::GetElem(int cur, ElemType& e) const
// 操作结果：用e返回结点cur元素值,如果不存在结点cur,函数返回NOT_PRESENT,否则返回ENTRY_FOUND
{
	if (cur < 0 || cur >= num)		// 不存在结点cur
		return NOT_PRESENT;			// 返回NOT_PRESENT
	else {	                        // 存在结点cur
		e = nodes[cur].data;		// 用e返回元素值
		return ENTRY_FOUND;			// 返回ENTRY_FOUND
	}
}

template <class ElemType>
Status ParentChildForest<ElemType>::SetElem(int cur, const ElemType& e)
// 操作结果：如果不存在结点cur,则返回FAIL,否则返回SUCCESS,并将结点cur的值设置为e
{
	if (cur < 0 || cur >= num)		// 不存在结点cur
		return FAIL;				// 返回FAIL
	else {	                    // 存在结点cur
		nodes[cur].data = e;		// 将结点cur的值设置为e
		return SUCCESS;	  		    // 返回SUCCESS
	}
}

template <class ElemType>
int ParentChildForest<ElemType>::NodeCount() const
// 操作结果：返回森林的结点个数
{
	return num;
}

template <class ElemType>
int ParentChildForest<ElemType>::FirstChild(int cur) const
// 操作结果：如cur无孩子,则返回-1,否则返回树结点cur的第一个孩子,
{
	Node<int>* p;
	if (cur < 0 || cur >= num)
		return -1;						// 结点cur不存在,返回-1表示无孩子

	if (nodes[cur].childLkList == NULL)	// 无孩子
		return -1;
	else
		return nodes[cur].childLkList->data;	// 取出第一个孩子
}

template <class ElemType>
int ParentChildForest<ElemType>::RightSibling(int cur) const
// 操作结果：如果结点cur无右兄弟,则返回-1,否则返回cur的右兄弟
{
	if (cur < 0 || cur >= num)
		return -1;						// 结点cur不存在,返回-1表示无孩子

	int pt = nodes[cur].parent;			// cur的双亲
	Node<int>* p = nodes[pt].childLkList;
	while (p != NULL && p->data != cur)
		p = p->next;
	if (p == NULL || p->next == NULL)
		return -1;				// 反回右兄弟
	else
		return p->next->data;	// 表示无右兄弟
}

template <class ElemType>
int ParentChildForest<ElemType>::Parent(int cur) const
// 操作结果：返回树结点cur的双亲
{
	if (cur < 0 || cur >= num)
		return -1;						// 结点cur不存在,返回-1表示无双亲
	return nodes[cur].parent;
}


template <class ElemType>
ParentChildForest<ElemType>::ParentChildForest(ElemType items[], int parents[], int r, int n, int size)
// 操作结果：建立数据元素为items[],对应结点双亲为parents[],根结点位置为r,结点个数为n的树
{
	maxSize = size;													// 最大结点个数
	if (n > maxSize)
		throw Error("结点个数太多!");								// 抛出异常
	nodes = new ChildParentTreeNode<ElemType>[maxSize];				// 分配存储空间
	for (int pos = 0; pos < n; pos++)
	{	// 依次对结点数据元素及双亲位置进行赋值
		nodes[pos].data = items[pos];								// 数据元素值
		nodes[pos].parent = parents[pos];							// 双亲位置
		if (parents[pos] != -1) {
			Node<int>* p, * newnode;
			newnode = new Node<int>(pos, NULL);
			if (nodes[parents[pos]].childLkList == NULL)
				nodes[parents[pos]].childLkList = newnode;
			else {
				p = nodes[parents[pos]].childLkList;
				while (p->next != NULL)
					p = p->next;
				p->next = newnode;
			}
		}
	}
	root = r;														// 根
	num = n;														// 结点个数
}