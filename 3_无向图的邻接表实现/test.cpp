#include "StayTime.h"
#include "Arc.h"
#include "Vex.h"
#include "BaseNode.h"
#include "Bigraph.h"
#include <iostream>

/*
 * ʾ������
 */

using namespace std;
using namespace liuyuan;

void test_stayTime()
{
	// ʹ�õ�һ�ֹ��캯������
	stayTime time1(10, 12, 1, 1);
	stayTime time2(11, 13, 1, 1);
	// ʹ�õڶ��ֹ��캯������
	stayTime time3({10, 1, 1, 13, 1, 1});
	cout << (time1 && time2) << endl;
	cout << time1.getTime(true) << endl;
	cout << time1.getTime(false) << endl;
	cout << time3.getTime(true) << endl;
}

void test_arc()
{
	// ���캯��ʾ��
	Arc Arc1(1, {10, 13, 1, 1, 1, 1});
	Arc Arc2(2, {11, 14, 1, 1, 1, 1}, &Arc1);

	cout << "Arc1: " << endl;
	cout << "Index: " << Arc1.getIndex() << endl;
	cout << "StayTime: \n\t";
	string temp = Arc1.getWeight().getTime(true);
	cout << temp << endl;
	temp = Arc1.getWeight().getTime(false);
	cout << temp << endl;
	cout << "Next: " << Arc1.getNext() << endl << endl;
}

void test_vex()
{
	// ����һ���洢Person�ڵ������
	Vex<Person> vex_p;
	cout << "Node num:\t" << vex_p.size() << endl;
	Person* p1 = new Person("��Ԫ");
	// ���ø�Ⱦʱ��
	p1->infected(14, 1, 1);
	cout << p1->getInfo() << endl;
	cout << p1->getName() << endl;
	cout << p1->getArc() << endl;
	vex_p.insertNode(p1);
	cout << "find: " << vex_p.find_name("��Ԫ") << endl;

	cout << "=======================================\n";

	// �����߽�㣬ͬʱ������뵽�ڵ���
	Arc* a1 = new Arc(1, {10, 14, 1, 1, 1, 1});
	// find_name����ʹ��ʵ��
	vex_p[vex_p.find_name("��Ԫ")]->insertArc(a1);
	cout << vex_p[0]->getArc()->getIndex() << endl;
	cout << vex_p[0]->getArc()->getWeight().getTime(true) << endl;
	cout << vex_p[0]->getArc()->getNext() << endl;
}

void test_bigraph()
{
	Bigraph g;
	// �����ͼ�в�������Person�ڵ㣬����Location�ڵ�
	g.insertPerson("P1");
	g.insertPerson("P2");
	g.insertLocation("L1");
	g.insertLocation("L2");
	// ����ߣ������ַ�ʽ����
	g.insertArc("P1", "L1", {10, 14, 1, 1, 1, 1} );
	g.insertArc(1, 1, {12, 15, 1, 1, 1, 1});
	for(auto i : g.visited_who(0))
	{
		cout << i << '\t';
	}
	cout << endl;
	for(auto i : g.visited_who("L2"))
	{
		cout << i << '\t';
	}
	cout << endl;
	for ( auto i : g.visited_where(0) )
	{
		cout << i << '\t';
	}
	cout << endl;
	for ( auto i : g.visited_where("P2"))
	{
		cout << i << '\t';
	}
}

int main()
{
	test_stayTime();
	test_arc();
	test_vex();
	test_bigraph();
}
