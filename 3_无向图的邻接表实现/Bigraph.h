#ifndef BIGRAPH
#define BIGRAPH

#include "Vex.h"
#include "BaseNode.h"
#include <string>
#include <initializer_list>
#include <vector>

#define PERSON		true
#define LOCATION	false

using std::initializer_list;
using std::string;

namespace liuyuan
{
	class Bigraph
	{
	private:
		Vex<Person> _vex_person;		// �洢Person�ڵ������
		Vex<Location> _vex_location;	// �洢Location�ڵ������
	public:
		// ����߽�㣬��Ҫ�����˵����֡��ص�����֡�����Ϊ6�Ĳ����б�
		void insertArc(const string& personName, const string& locationName, initializer_list<int> iList);
		// ����߽�㣬��Ҫ�����˵��±꣬�ص���±ꡢ����Ϊ6�Ĳ����б�
		void insertArc(const size_t& personIndex, const size_t& locationIndex, initializer_list<int> iList);
		// �����˽ڵ㣬�����˵�����
		void insertPerson(const string& name);
		// ����ص�ڵ㣬����ص������
		void insertLocation(const string& name);
		
		// ����vector�����д洢����������ط����˵��±�
		vector<int> visited_who(const string& locationName);
		vector<int> visited_who(const size_t& locationIndex);
		// ����vector�����д洢�������ȥ���ĵط����±�
		vector<int> visited_where(const string& personName);
		vector<int> visited_where(const size_t& personName);
	};
}

#endif // !BIGRAPH

