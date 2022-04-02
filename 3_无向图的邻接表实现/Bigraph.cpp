#include "Bigraph.h"
#include <cassert>
#include <iostream>
#include <initializer_list>
#include <string>
#include <vector>

using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std::initializer_list;
using std::string;
using std::vector;

namespace liuyuan
{
	void Bigraph::insertArc(const string& personName, const string& locationName, initializer_list<int> iList)
	{
		size_t personIndex = this->_vex_person.find_name(personName);
		if (personIndex < 0) 
		{
			cerr << __FILE__ << endl;
			cerr << __LINE__ << endl;
			cerr << __func__ << endl;
			cerr << "===== Person Name NOT FOUND =====" << endl;
			return;
		}
		size_t locationIndex = this->_vex_location.find_name(locationName);
		if (locationIndex < 0) 
		{
			cerr << __FILE__ << endl;
			cerr << __LINE__ << endl;
			cerr << __func__ << endl;
			cerr << "===== Location Name NOT FOUND =====" << endl;
			return;
		}
		insertArc(personIndex, locationIndex, iList);
			}

	void Bigraph::insertArc(const size_t& personIndex, const size_t& locationIndex, initializer_list<int> iList)
	{
		assert(personIndex >=0 && personIndex < this->_vex_person.size());
		assert(locationIndex >= 0 && locationIndex < this->_vex_location.size());

		this->_vex_person[personIndex]->insertArc(new Arc(locationIndex,iList));
		this->_vex_location[locationIndex]->insertArc(new Arc(personIndex, iList));
	}

	void Bigraph::insertPerson(const string &name)
	{
		this->_vex_person.insertNode(new Person(name));
	}

	void Bigraph::insertLocation(const string &name)
	{
		this->_vex_location.insertNode(new Location(name));
	}

	vector<int> Bigraph::visited_who(const string& locationName)
	{
		size_t index = this->_vex_location.find_name(locationName);
		return visited_who(index);
	}

	vector<int> Bigraph::visited_who(const size_t& locationIndex)
	{
		assert(locationIndex >= 0 || locationIndex < this->_vex_location.size());
		vector<int> result;
		Arc* ite = this->_vex_location[locationIndex]->getArc();
		while(ite) 
		{
			result.push_back(ite->getIndex());
			ite = ite->getNext(); 
		}
		return result;
	}

	vector<int> Bigraph::visited_where(const string& personName)
	{
		size_t index = this->_vex_person.find_name(personName);
		return visited_where(index);
	}

	vector<int> Bigraph::visited_where(const size_t& personIndex)
	{
		assert(personIndex >= 0 && personIndex < this->_vex_person.size());
		vector<int> result;
		Arc* ite = this->_vex_person[personIndex]->getArc();
		while(ite)
		{
			result.push_back(ite->getIndex());
			ite = ite->getNext();
		}
		return result;
	}
}
