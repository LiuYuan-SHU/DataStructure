#include "Arc.h"
#include <cassert>
#include <initializer_list>

using std::initializer_list;

namespace liuyuan
{
	Arc::Arc(size_t index, initializer_list<int> weightInit, Arc* next) : _index(index), _weight(weightInit), _next(next)
	{

	}

	void Arc::setWeight(bool isFirst, initializer_list<int> iList)
	{
		assert(iList.size() == 3);
		this->_weight.setTime(isFirst, *construct_tm(iList)); 
	}
}
