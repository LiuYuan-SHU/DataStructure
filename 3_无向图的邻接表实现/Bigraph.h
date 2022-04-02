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
		Vex<Person> _vex_person;		// 存储Person节点的数组
		Vex<Location> _vex_location;	// 存储Location节点的数组
	public:
		// 插入边结点，需要输入人的名字、地点的名字、长度为6的参数列表
		void insertArc(const string& personName, const string& locationName, initializer_list<int> iList);
		// 插入边结点，需要输入人的下标，地点的下标、长度为6的参数列表
		void insertArc(const size_t& personIndex, const size_t& locationIndex, initializer_list<int> iList);
		// 插入人节点，输入人的名字
		void insertPerson(const string& name);
		// 插入地点节点，输入地点的名字
		void insertLocation(const string& name);
		
		// 返回vector，其中存储着来过这个地方的人的下标
		vector<int> visited_who(const string& locationName);
		vector<int> visited_who(const size_t& locationIndex);
		// 返回vector，其中存储着这个人去过的地方的下标
		vector<int> visited_where(const string& personName);
		vector<int> visited_where(const size_t& personName);
	};
}

#endif // !BIGRAPH

