#pragma once
#include"Node.h"
#include"Assistance.h"
template<class ElemType>
class ParentChildForest
{
protected:
	// 森林的数据成员
	ChildParentTreeNode<ElemType>* nodes;			// 存储树结点
	int maxSize;									// 树结点最大个数 
	int root, num;									// 根的位置及结点数

	//	辅助函数:
	void PreRootOrderHelp(int r, void (*Visit)(const ElemType&)) const;	// 先根序遍历
	void PostRootOrderHelp(int r, void (*Visit)(const ElemType&)) const;	// 后根序遍历
	int HeightHelp(int r) const;					// 返回以r为根的高
	int DegreeHelp(int r) const;					// 返回以r为根的树的度

public:
	ParentChildForest();							//无参构造函数
	virtual ~ChildParentTree();						// 析构函数
};