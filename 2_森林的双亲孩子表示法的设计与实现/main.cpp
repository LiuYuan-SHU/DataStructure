#include"parent_child_forest.h"

int main()
{
	char items[] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P' };
	int parents[] = { -3,0,0,-3,3,4,-10,6,6,6,7,7,9,9,9,12 };      //-1表示每棵树的根节点
	ChildParentForestNode<char> newnode('Q', 13, NULL);
	ChildParentForestNode<char> newnode_test1('A', 13, NULL);
	ChildParentForestNode<char> newnode_test2('R', 17, NULL);
	ParentChildForest<char> t(items, parents, 16, 0);
	cout << endl << "森林的规模:";
	cout << t.getTreeNum();
	cout << endl << "森林的高度:";
	cout << t.MaxHeigth();
	cout << endl << "叶子结点的个数:";
	cout << t.getLeafNum();
	t.Show();
	cout << endl << "先根遍历:";
	t.PreRootOrder();
	cout << endl << "中根遍历:";
	t.InorderRootOrder();
	cout << endl << "后根遍历:";
	t.PostRootOrderOrder();
	cout << endl << "添加结点函数:";
	cout << endl << "添加结点Q，其双亲为13:";
	t.append(newnode);
	t.Show();

	try {
		cout << endl << "添加结点函数测试:";
		t.append(newnode_test1);
	}
	catch (Error& e) {
		e.Show();
	}

	try {
		cout << endl << "添加结点函数测试:";
		t.append(newnode_test2);
	}
	catch (Error& e) {
		e.Show();
	}

	cout << endl << "删除结点函数:";
	cout << endl << "删除第四位的结点:";
	t.delnode(4);
	t.Show();
	try {
		cout << endl << "删除结点函数测试:";
		t.delnode(-2);
	}
	catch (Error& e) {
		e.Show();
	}

	cout << endl << "删除孩子函数:";
	t.delchild(0, 1);
	t.Show();
	try {
		cout << endl << "删除孩子函数测试:";
		cout << "删除0位的第二个孩子" << endl;
		t.delchild(0, 2);
	}
	catch (Error& e) {
		e.Show();
	}
	try {
		cout << endl << "删除孩子函数测试:";
		cout << "删除1位的第二个孩子" << endl;
		t.delchild(1, 2);
	}
	catch (Error& e) {
		e.Show();
	}


	cout << endl << "修改双亲结点函数";
	t.Modifyparent(0, 6);
	t.Show();
	try {
		cout << endl << "修改双亲结点函数测试:";
		t.Modifyparent(-1, 6);
	}
	catch (Error& e) {
		e.Show();
	}
	try {
		cout << endl << "修改双亲结点函数测试:";
		t.Modifyparent(1, 18);
	}
	catch (Error& e) {
		e.Show();
	}

	ParentChildForest<char> t2(NULL, NULL, 0, 0);
	cout << endl << "森林的规模:";
	cout << t2.getTreeNum();
	cout << endl << "森林的高度:";
	cout << t2.MaxHeigth();
	cout << endl << "叶子结点的个数:";
	cout << t2.getLeafNum();
	t2.Show();
	try {
		t2.delnode(0);
	}
	catch (Error& e) {
		e.Show();
	}

	try {
		cout << endl << "删除孩子函数测试:";
		cout << "删除0位的第二个孩子" << endl;
		t.delchild(0, 2);
	}
	catch (Error& e) {
		e.Show();
	}

	cout << endl;
	try {
		ParentChildForest<char> t3(NULL, NULL, 1001, 0);
	}
	catch (Error& e) {
		e.Show();
	}

}