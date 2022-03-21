#pragma once
#include"Node.h"
#include"child_parent_forest_node.h"
//#include"LinkQueue.h"
#include"Assistance.h"

//#include <stack>
//#include <queue>
//#include <algorithm>
//
//using std::stack;
//using std::queue;

template<class ElemType>
class ParentChildForest
{
protected:
	// 森林的数据成员
	ChildParentForestNode<ElemType>* nodes;					// 存放森林中所有结点
	int num_of_tree;										// 森林中树的数目
	int num;												// 森林总结点个数
	int maxSize;											// 森林结点最大数
	int first_root;											// 森林第一个根节点

	//	辅助函数:
	void PreRootOrderHelp(int r) const;						// 先根序遍历
	void InorderRootOrderHelp(int r) const;					// 中根序遍历
	void PostRootOrderHelp(int r) const;					// 后根序遍历
	//inline void PostRootOrderHelp_childTree(int r) const;	// 后根遍历辅助函数，遍历子树
	int HeightHelp(int r) const;							// 返回以r为根的树的度

public:
	ParentChildForest();							// 无参构造函数
	ParentChildForest(ElemType items[], int parents[], int n, int r, int size = DEFAULT_SIZE);
	virtual ~ParentChildForest();					// 析构函数
	bool Empty() const;								// 判断森林是否为空
	Status GetElem(int cur, ElemType& e) const;		// 用e返回结点元素值
	Status SetElem(int cur, const ElemType& e);		// 将结cur的值置为e
	int NodeCount() const;
	int FirstChild(int cur) const;					// 返回结点cur的第一个孩子   【查】
	int RightSibling(int cur) const;				// 返回结点cur的右兄弟	   【查】
	int Parent(int cur) const;
	void Show();
	int getTreeNum();
	int getNum();
	ChildParentForestNode<ElemType> getNode(int i);
	//获取树的棵树
	void PreRootOrder();							// 森林的先根遍历
	void InorderRootOrder();						// 森林的先根遍历
	void PostRootOrderOrder();						// 森林的后根遍历
	int getLeafNum();								// 获取叶子结点数量
	template<class T>
	friend ParentChildForest<T>* operator + (ParentChildForest<T>& t1, ParentChildForest<T>& t2); //森林相加
	Status append(ChildParentForestNode<ElemType> new_node);   // 添加结点
	Status delnode(int pos);								   // 删除结点
	Status delchild(int pos,int child_pos);					   // 删除孩子
	Status Modifyparent(int pos, int parent);                  // 修改双亲
	int MaxHeigth();										   //获得森林的最大高度	

};




template<class ElemType>
ParentChildForest<ElemType>::ParentChildForest()
{
	maxSize = DEFAULT_SIZE;									// 树结点最大个数
	nodes = new ChildParentForestNode<ElemType>[maxSize];	// 分配存储空间
	//root = NULL;			
	num = 0;												// 空森的结点个数为0
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
	else {							// 存在结点cur
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
		return -1;								// 结点cur不存在,返回-1表示无孩子

	if (nodes[cur].childLkList == NULL)			// 无孩子
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
	if (nodes[cur].Tag == "ROOT")
	{
		int i = cur;
		// find the next root node
		do {
			i++;
			if (i >= num) { return -1; }
		} while (nodes[i].Tag != "ROOT");
		//protection


		return i;
	}

	int pt = nodes[cur].parent;			// cur的双亲
	if (pt < 0 || pt >= num) return -1;
	Node<int>* p = nodes[pt].childLkList;
	while (p != NULL && p->data != cur)
		p = p->next;
	if (p == NULL || p->next == NULL)
		return -1;				// 表示无右兄弟
	else
		return p->next->data;	// 返回右兄弟
}

template <class ElemType>
int ParentChildForest<ElemType>::Parent(int cur) const
// 操作结果：返回树结点cur的双亲
{
	if (cur < 0 || cur >= num)
		return -1;						// 结点cur不存在,返回-1表示无双亲
	return nodes[cur].parent;
}


//还在修改//
template <class ElemType>
ParentChildForest<ElemType>::ParentChildForest(ElemType items[], int parents[], int n, int r, int size)
// 操作结果：建立数据元素为items[],对应结点双亲为parents[],根结点位置为r,结点个数为n的 森林
{
	num_of_tree = 0;
	maxSize = size;													// 最大结点个数
	num = n;														// 结点个数
	first_root = r;													// 记录森林的第一树的根节点

	if (n > maxSize) {
		throw Error("结点个数太多!");								    // 抛出异常
	}

	nodes = new ChildParentForestNode<ElemType>[maxSize];		    // 分配存储空间
	for (int pos = 0; pos < n; pos++)
	{	// 依次对结点数据元素及双亲位置进行赋值
		nodes[pos].data = items[pos];								// 数据元素值
		nodes[pos].parent = parents[pos];							// 双亲位置
		nodes[pos].childLkList = NULL;

		if (parents[pos] < 0) {			         //计算根节点个数 获得树的数量
			num_of_tree++;
			nodes[pos].Tag = "ROOT";		//将该森林结点设置为树根
		}


		if (parents[pos] >= 0) {
			nodes[pos].Tag = "UROOT";		//将该森林结点设置为非树根
			Node<int>* p, * q;
			q = new Node<int>(pos, NULL);
			if (nodes[parents[pos]].childLkList == NULL)            //如果第一个孩子是空，则直接将q设置为第一个孩子
				nodes[parents[pos]].childLkList = q;
			else {
				for (p = nodes[parents[pos]].childLkList; p->next != NULL; p = p->next);  //寻找到尾部
				p->next = q;										//添加下一个结点
			}
		}
	}

}

template<class ElemType>
void ParentChildForest<ElemType>::Show()
{	
	cout << endl;
	if (num == 0) cerr << "森林为空" << endl;
	for (int i = 0; i < num; i++) {
		std::cout <<setw(2)<< i<<" ";
		if (nodes[i].Tag == "ROOT")
			std::cout << setw(2) << nodes[i].Tag;
		else cout << "    " ;
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
	// Original Version
	if (r < 0 || r > num)
		return;
	if (nodes[r].childLkList != NULL) PostRootOrderHelp(FirstChild(r));
	PostRootOrderHelp(RightSibling(r));
	std::cout << nodes[r].data;
}

template<class ElemType>
inline int ParentChildForest<ElemType>::HeightHelp(int r) const
{	
	int maxHeight=0;					//最大高度
	int temp = 0;
	Node<int>* p;
	for (p = nodes[r].childLkList; p != NULL; p = p->next) {
		if ((temp = HeightHelp(p->data)) > maxHeight) maxHeight = temp;
	}
	return maxHeight+1;
}

template<class ElemType>
void ParentChildForest<ElemType>::PreRootOrder()
{
	PreRootOrderHelp(first_root);
}

template<class ElemType>
inline void ParentChildForest<ElemType>::InorderRootOrder()
{
	InorderRootOrderHelp(first_root);
}

template<class ElemType>
void ParentChildForest<ElemType>::PostRootOrderOrder()
{
	PostRootOrderHelp(first_root);
}

template<class ElemType>
int ParentChildForest<ElemType>::getLeafNum()
{
	int sum = 0;
	for (int i = 0; i < num; i++) {
		if (nodes[i].childLkList == NULL && nodes[i].Tag != "ROOT") sum++;
	}
	return sum;
}

template<class ElemType>
Status ParentChildForest<ElemType>::append(ChildParentForestNode<ElemType> new_node)
{
	//增加结点于nodes中
	ChildParentForestNode<ElemType>* temp = new ChildParentForestNode<ElemType>[maxSize + 1];
	for (int i = 0; i < num; i++) {
		temp[i] = nodes[i];
		if (nodes[i].data == new_node.data) throw Error("已存在相同命名的结点");
	}
	temp[num] = new_node;
	temp[num].Tag = "UROOT";
	nodes = temp;
	if (new_node.parent >= 0 && new_node.parent < num) {   //判断双亲是否存在 
		int pn = new_node.parent;
		Node<int>* p;
		Node<int>* q = new Node<int>(num, NULL);
		if (nodes[pn].childLkList == NULL) nodes[pn].childLkList = q;
		else {
			for (p = nodes[pn].childLkList; p->next != NULL; p = p->next);
			p->next = q;
		}
		nodes[pn].Tag = "UROOT";
	}
	else throw Error("添加的结点双亲不存在");
	num++;
	return SUCCESS;
}

template<class ElemType>
Status ParentChildForest<ElemType>::delnode(int pos)
{
	//将结点
	ChildParentForestNode<ElemType>* temp = new ChildParentForestNode<ElemType>[maxSize];
	if (num - 1 == pos) { num--; return SUCCESS; }
	if (pos < 0 || pos >= num) throw Error("删除的坐标越界");
	nodes[pos] = nodes[num];//把所有的pos孩子删除 通过双亲  把所有的num孩子换成pos

	nodes[pos] = nodes[num - 1];
	Node<int>* p;
	Node<int>* q;
	int pn = nodes[pos].parent;
	int pnum = nodes[num - 1].parent;
	if (pn >= 0 && pn < num)
		for (p = nodes[pn].childLkList, q = p; p != NULL; q = p, p = p->next)
		{
			if (p->data == pos) {
				q->next = p->next;   //将含有pos 的孩子删除
			}
		}

	if (nodes[pnum].childLkList != NULL)
		for (p = nodes[pnum].childLkList; p != NULL; p = p->next)
		{
			if (p != NULL && p->data == num - 1) {
				p->data = pos;   //将含有num 的孩子修改为pos
			}
		}
	num--;
	return SUCCESS;
}

template<class ElemType>
inline Status ParentChildForest<ElemType>::delchild(int pos, int child_pos)
{	
	Node<int>* p;
	Node<int>* q;
	int count = 0;
	if (nodes[pos].childLkList == NULL) throw Error("该结点无孩子");
	for (p = nodes[pos].childLkList, q = p, count = 0; count < child_pos; q = p, p = p->next, count++) {
		if (p == NULL) throw Error("孩子坐标越界");
	};
	nodes[p->data].parent = -1;//修改删除孩子的双亲
	//Modifyparent(p->data,-1); 
	q->next = p->next;
	//至此 完成在结点中删除孩子的操作
	return SUCCESS;
}

template<class ElemType>
inline Status ParentChildForest<ElemType>::Modifyparent(int pos, int Parent)
{
	Node<int>* p;
	Node<int>* q;
	if (pos<0 || pos>=num) throw Error("定位结点坐标越界");
	if (Parent <0 || Parent >=num) throw Error("定位双亲坐标越界");
	if (nodes[pos].parent >= 0) {
		for (p = nodes[nodes[pos].parent].childLkList, q = p; p != NULL; q = p, p = p->next) {  //减少孩子
			if (p->data == pos) {
				q->next = p->next;
			}
		}
	}
	nodes[pos].parent = Parent;
	if (nodes[pos].Tag == "ROOT") nodes[pos].Tag = "UROOT";
	Node<int>* new_node = new Node<int>(pos, NULL);       //增加孩子
	if (nodes[Parent].childLkList == NULL) nodes[Parent].childLkList = new_node;
	else {
		for (p = nodes[Parent].childLkList; p->next != NULL; p = p->next);
		p->next = new_node;
	}
	return SUCCESS;
}

template<class ElemType>
int ParentChildForest<ElemType>::MaxHeigth()
{	
	int max=0;
	int temp=0;
	for (int i = 0; i < num; i++)
	{
		if (nodes[i].Tag == "ROOT")
		{
			if((temp= HeightHelp(i))>=max) max=temp;
		}
	}
	return max;
}


template<class T>
ParentChildForest<T>* operator+(ParentChildForest<T>& t1, ParentChildForest<T>& t2)
{
	ParentChildForest<T>* result = new ParentChildForest<T>;
	for (int i = 0; i < t1.getNum(); i++) {
		result->append(t1.getNode(i));
	}
	for (int i = 0; i < t2.getNum(); i++) {
		result->append(t2.getNode(i));
	}
	return result;
}
