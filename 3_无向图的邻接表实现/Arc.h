#ifndef ARC
#define ARC

#include "StayTime.h"
#include <initializer_list>
#include <string>

using std::string;
using std::initializer_list;

namespace liuyuan
{
	class Arc
	{
	private:
		size_t _index;				// 记录边结点在Vex中的下标
		stayTime _weight;			// 记录这个人在什么时候来过、离开这个地点
		Arc* _next;					// 记录后驱
	public:
		// 构造函数，需要输入这个边结点对应的节点下标， 
		// 第二个参数的初始化列表长度为6，按照进入：hour, day, month；离开：hour,day,month
		// 默认后驱为空
		Arc(size_t index, initializer_list<int> weightInit, Arc* next = nullptr);

		// getter
		// 获取对应节点下标
		size_t getIndex() const { return this->_index; }
		// 获取后驱
		Arc* getNext() const { return this->_next; }
		// 获取进入、离开时间
		stayTime& getWeight() { return this->_weight; }

		// setter
		// 设置下标
		void setIndex(size_t index) { this->_index = index; }
		// 设置时间，初始化列表长度为3
		void setWeight(bool isFirst, initializer_list<int> iList);
		// 设置后驱
		void setNext(Arc* next) { this->_next = next; }
	};
}

#endif
