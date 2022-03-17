#include"parent_child_forest.h"

int main()
{	
	try {
		char items[] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P'};
		int parents[] = { -3,0,0,-3,3,4,-10,6,6,6,7,7,9,9,9,12};      //-1表示每棵树的根节点
		ChildParentForestNode<char> newnode('F', 0, NULL);
		ParentChildForest<char> t(items, parents, 16, 0);
		cout << endl << "森林的规模:";
		cout << t.getTreeNum() << endl;
		cout << endl << "先根遍历:";
		t.PreRootOrder();
		cout << endl << "中根遍历:";
		t.InorderRootOrder();
		cout << endl << "后根遍历:";
		t.PostRootOrderOrder();
		cout << endl << "叶子结点的个数:";
		cout << t.getLeafNum();
		cout << endl << "添加结点函数测试:";
		t.append(newnode);
		t.Show();
		cout << endl << "删除结点函数测试:";
		t.delnode(4);
		t.Show();
		cout << endl << "修改双亲结点函数测试:";
		t.Modifyparent(1, 2);
		//t.Modifyparent(-1, 2);
		t.Show();
		//(t + t)->Show();
	}
	catch (Error&e ) {
		e.Show();
	}

}