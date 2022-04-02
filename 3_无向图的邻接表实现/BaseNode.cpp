#include "BaseNode.h"
#include "StayTime.h"
#include <cassert>
#include <ctime>
#include <initializer_list>
#include <string>
#include <time.h>

using std::string;
using std::initializer_list;

namespace liuyuan
{
	Node::~Node()
	{
		if ( Arc* ite = _firstArc )
		{
			Arc* temp;
			while ( temp = ite++ ) { delete temp; }
		}
	}

	void Node::insertArc(Arc* newArc)
	{
		if (Arc* ite = this->_firstArc)
		{
			while (ite->getNext() != nullptr) { ite = ite->getNext(); }
			ite->setNext(newArc);
		}
		else
		{
			this->_firstArc = newArc;
		}
	}

	Person::Person(const string& name, initializer_list<int> infectionInfo) : Node(name)
	{
		assert(infectionInfo.size() == 0 || infectionInfo.size() == 3);

		this->_infectionTime = infectionInfo.size() == 0 ? ( nullptr ) : ( construct_tm(infectionInfo));
	}

	Person::~Person()
	{
		if (this->_infectionTime) { delete this->_infectionTime; }
	}

	void Person::infected(int hour, int day, int month)
	{
		assert(day != 0 && month != 0);

		this->_infectionTime = construct_tm(initializer_list<int>{hour, day, month});	
	}

	string Person::getInfo() const
	{
		string infection;
		if (_infectionTime)
		{
			char buffer[1024];
			strftime(buffer, 1024, "%B: Day %d: Hour %H", this->_infectionTime);
			infection = string("Infection Time: ") + string(buffer);
		}
		else
		{
			infection = "Not Infected";
		}
		return "Name: " + this->_name + '\n' + infection;
	}

	string Location::getInfo() const
	{
		return string("µØµãÃû³Æ£º " + this->_name + "\n");
	}
}
