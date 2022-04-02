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
		// ����
		string _name;
		// ָ���һ���˻�ص�
		Arc* _firstArc;
	public:
		// ���캯��
		Node(string name) : _name(name), _firstArc(nullptr) {}
		// ��������
		Node(const Node& other);
		// ��������
		virtual ~Node();

		// ��ӱ�
		void insertArc(Arc* newArc);

		bool operator==(string name) { return this->_name == name; }

		// ��ȡ����
		string getName() const { return _name; }
		// ��ȡ��
		Arc* getArc() const { return _firstArc; }
		// ��ȡ��Ϣ
		virtual string getInfo() const = 0;
	};

	class Person : public Node
	{
	private:
		tm* _infectionTime;		// ��Ⱦʱ�䣬���Ϊ�գ���δ��Ⱦ
	public:
		Person(const string& name, std::initializer_list<int> infectionInfo = {});
		~Person();

		// ���ø�Ⱦ
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
