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
		size_t _index;				// ��¼�߽����Vex�е��±�
		stayTime _weight;			// ��¼�������ʲôʱ���������뿪����ص�
		Arc* _next;					// ��¼����
	public:
		// ���캯������Ҫ��������߽���Ӧ�Ľڵ��±꣬ 
		// �ڶ��������ĳ�ʼ���б���Ϊ6�����ս��룺hour, day, month���뿪��hour,day,month
		// Ĭ�Ϻ���Ϊ��
		Arc(size_t index, initializer_list<int> weightInit, Arc* next = nullptr);

		// getter
		// ��ȡ��Ӧ�ڵ��±�
		size_t getIndex() const { return this->_index; }
		// ��ȡ����
		Arc* getNext() const { return this->_next; }
		// ��ȡ���롢�뿪ʱ��
		stayTime& getWeight() { return this->_weight; }

		// setter
		// �����±�
		void setIndex(size_t index) { this->_index = index; }
		// ����ʱ�䣬��ʼ���б���Ϊ3
		void setWeight(bool isFirst, initializer_list<int> iList);
		// ���ú���
		void setNext(Arc* next) { this->_next = next; }
	};
}

#endif
