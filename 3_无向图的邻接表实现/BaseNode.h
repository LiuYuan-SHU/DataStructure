#ifndef BASE_NODE
#define BASE_NODE

#include "Arc.h"
#include <ctime>
#include <initializer_list>
#include <string>

using std::string;
using std::tm;

namespace liuyuan 
{
	class Node
	{
	protected:
		// 名称
		string _name;
		// 指向第一个人或地点
		Arc* _firstArc;
	public:
		// 构造函数
		Node(string name) : _name(name), _firstArc(nullptr) {}
		// 拷贝函数
		Node(const Node& other);
		// 析构函数
		virtual ~Node();

		// 添加边
		void insertArc(Arc* newArc);

		bool operator==(string name) { return this->_name == name; }

		// 获取名字
		string getName() const { return _name; }
		// 获取边
		Arc* getArc() const { return _firstArc; }
		// 获取信息
		virtual string getInfo() const = 0;
	};

	class Person : public Node
	{
	private:
		tm* _infectionTime;		// 感染时间，如果为空，则未感染
	public:
		Person(const string& name, std::initializer_list<int> infectionInfo = {});
		~Person();

		// 设置感染
		void infected(int hour, int day, int month);
		bool isInfected() const { return _infectionTime != nullptr; }
		string getInfo() const;
	};

	class Location : public Node
	{
	public:
		Location(string name) : Node(name) {}
		string getInfo() const;
	};
}

#endif
