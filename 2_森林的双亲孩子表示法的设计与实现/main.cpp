#include"parent_child_forest.h"

int main()
{
	char items[] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P' };
	int parents[] = { -3,0,0,-3,3,4,-10,6,6,6,7,7,9,9,9,12 };      //-1��ʾÿ�����ĸ��ڵ�
	ChildParentForestNode<char> newnode('Q', 13, NULL);
	ChildParentForestNode<char> newnode_test1('A', 13, NULL);
	ChildParentForestNode<char> newnode_test2('R', 17, NULL);
	ParentChildForest<char> t(items, parents, 16, 0);
	cout << endl << "ɭ�ֵĹ�ģ:";
	cout << t.getTreeNum();
	cout << endl << "ɭ�ֵĸ߶�:";
	cout << t.MaxHeigth();
	cout << endl << "Ҷ�ӽ��ĸ���:";
	cout << t.getLeafNum();
	t.Show();
	cout << endl << "�ȸ�����:";
	t.PreRootOrder();
	cout << endl << "�и�����:";
	t.InorderRootOrder();
	cout << endl << "�������:";
	t.PostRootOrderOrder();
	cout << endl << "��ӽ�㺯��:";
	cout << endl << "��ӽ��Q����˫��Ϊ13:";
	t.append(newnode);
	t.Show();

	try {
		cout << endl << "��ӽ�㺯������:";
		t.append(newnode_test1);
	}
	catch (Error& e) {
		e.Show();
	}

	try {
		cout << endl << "��ӽ�㺯������:";
		t.append(newnode_test2);
	}
	catch (Error& e) {
		e.Show();
	}

	cout << endl << "ɾ����㺯��:";
	cout << endl << "ɾ������λ�Ľ��:";
	t.delnode(4);
	t.Show();
	try {
		cout << endl << "ɾ����㺯������:";
		t.delnode(-2);
	}
	catch (Error& e) {
		e.Show();
	}

	cout << endl << "ɾ�����Ӻ���:";
	t.delchild(0, 1);
	t.Show();
	try {
		cout << endl << "ɾ�����Ӻ�������:";
		cout << "ɾ��0λ�ĵڶ�������" << endl;
		t.delchild(0, 2);
	}
	catch (Error& e) {
		e.Show();
	}
	try {
		cout << endl << "ɾ�����Ӻ�������:";
		cout << "ɾ��1λ�ĵڶ�������" << endl;
		t.delchild(1, 2);
	}
	catch (Error& e) {
		e.Show();
	}


	cout << endl << "�޸�˫�׽�㺯��";
	t.Modifyparent(0, 6);
	t.Show();
	try {
		cout << endl << "�޸�˫�׽�㺯������:";
		t.Modifyparent(-1, 6);
	}
	catch (Error& e) {
		e.Show();
	}
	try {
		cout << endl << "�޸�˫�׽�㺯������:";
		t.Modifyparent(1, 18);
	}
	catch (Error& e) {
		e.Show();
	}

	ParentChildForest<char> t2(NULL, NULL, 0, 0);
	cout << endl << "ɭ�ֵĹ�ģ:";
	cout << t2.getTreeNum();
	cout << endl << "ɭ�ֵĸ߶�:";
	cout << t2.MaxHeigth();
	cout << endl << "Ҷ�ӽ��ĸ���:";
	cout << t2.getLeafNum();
	t2.Show();
	try {
		t2.delnode(0);
	}
	catch (Error& e) {
		e.Show();
	}

	try {
		cout << endl << "ɾ�����Ӻ�������:";
		cout << "ɾ��0λ�ĵڶ�������" << endl;
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