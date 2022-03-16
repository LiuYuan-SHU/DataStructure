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
	void PreRootOrderHelp(int r, void (*Visit)(const ElemType&)) const;	// 先根序遍历
	void PostRootOrderHelp(int r, void (*Visit)(const ElemType&)) const;	// 后根序遍历
	int HeightHelp(int r) const;					// 返回以r为根的高
	int DegreeHelp(int r) const;					// 返回以r为根的树的度

public:
	ParentChildForest();							//无参构造函数
	virtual ~ParentChildForest();						// 析构函数
	bool Empty() const;								//判断森林是否为空
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