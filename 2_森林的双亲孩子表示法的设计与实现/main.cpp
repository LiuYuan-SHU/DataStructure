#include"parent_child_forest.h"

int main()
{	
	char items[] = { 'A','B','C','D','E'};
	int parents[] = { -3,0,0,0,-1};      //-1��ʾÿ�����ĸ��ڵ�
	ParentChildForest<char> t(items, parents,5);
	t.Show();
	cout <<endl<< "ɭ�ֵĹ�ģ:";
	cout << t.getTreeNum() << endl;
}