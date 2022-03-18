#include"parent_child_forest.h"

int main()
{	
	try {
		char items[] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P'};
		int parents[] = { -3,0,0,-3,3,4,-10,6,6,6,7,7,9,9,9,12};      //-1��ʾÿ�����ĸ��ڵ�
		ChildParentForestNode<char> newnode('F', 0, NULL);
		ParentChildForest<char> t(items, parents, 16, 0);
		cout << endl << "ɭ�ֵĹ�ģ:";
		cout << t.getTreeNum() << endl;
		cout << endl << "�ȸ�����:";
		t.PreRootOrder();
		cout << endl << "�и�����:";
		t.InorderRootOrder();
		cout << endl << "�������:";
		t.PostRootOrderOrder();
		cout << endl << "Ҷ�ӽ��ĸ���:";
		cout << t.getLeafNum();
		cout << endl << "��ӽ�㺯������:";
		t.append(newnode);
		t.Show();
		cout << endl << "ɾ����㺯������:";
		t.delnode(4);
		t.Show();
		cout << endl << "�޸�˫�׽�㺯������:";
		t.Modifyparent(1, 2);
		//t.Modifyparent(-1, 2);
		t.Show();
		//(t + t)->Show();
	}
	catch (Error&e ) {
		e.Show();
	}

}