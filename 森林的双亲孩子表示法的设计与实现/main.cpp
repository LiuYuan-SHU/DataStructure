#include"parent_child_forest.h"

int main()
{	
	char items[] = { 'A','B','C','D','E'};
	int parents[] = { -3,0,0,0,-1};      //-1表示每棵树的根节点
	ParentChildForest<char> t(items, parents,5);
	t.Show();
	cout <<endl<< "森林的规模:";
	cout << t.getTreeNum() << endl;
}