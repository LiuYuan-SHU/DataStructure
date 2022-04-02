#include "StayTime.h"
#include <iostream>
#include <cassert>
#include <initializer_list>
#include <time.h>

using std::cout;
using std::cin;
using std::endl;

namespace liuyuan 
{
	stayTime::stayTime(int i_hour, int o_hour, int i_day, int o_day, int i_month, int o_month)
	{
		construct_tm(this->_time_entrance, {i_hour, i_day, i_month});
		construct_tm(this->_time_leave, {o_hour, o_month, o_month});
	}

	// stayTime���캯����Ҫ���ʼ���б�һ��ҪΪ6
	// ͬʱ��������˳��Ϊ������hour, day, month�� �뿪hour, day, month
	stayTime::stayTime(initializer_list<int> iList)
	{
		assert(iList.size() == 6);
		
		construct_tm(this->_time_entrance,  { *(iList.begin()), *(iList.begin() + 1), *(iList.begin() + 2) });
		construct_tm(this->_time_leave, { *(iList.begin() + 3), *(iList.begin() + 4), *(iList.begin() + 5) });
	}

	stayTime::stayTime(const stayTime& otherTime)
	{
		stayTime(otherTime._time_entrance.tm_hour,
					otherTime._time_entrance.tm_mday,
					otherTime._time_entrance.tm_mon,
					otherTime._time_leave.tm_hour,
					otherTime._time_leave.tm_mday,
					otherTime._time_leave.tm_mon
				);
	}

	bool stayTime::operator&&(const stayTime &rightTime) const
	{
		return (
				// �·���ͬ
				( 
					this->_time_entrance.tm_mon == rightTime._time_entrance.tm_mon
				) &&
				// ����ͬ
				(
					this->_time_entrance.tm_mday == rightTime._time_entrance.tm_mday
				) &&
				// ʱ���н�����һ���˵Ľ���ʱ������һ���˵Ľ���ʱ��֮���뿪ʱ��֮ǰ
				(
					(
						rightTime._time_entrance.tm_hour <= this->_time_entrance.tm_hour && this->_time_entrance.tm_hour <= rightTime._time_leave.tm_hour
					) ||
					(
						this->_time_entrance.tm_hour <= rightTime._time_entrance.tm_hour && rightTime._time_entrance.tm_hour <= this->_time_leave.tm_hour
					)
				)
			);
	}

	string stayTime::getTime(bool isEntrance)
	{
		tm* des = isEntrance ? (&(this->_time_entrance)) : (&(this->_time_leave));
		char buffer[1024];
		strftime(buffer, 1024, "%B: Day %d: Hour %H", des);
		return buffer;
	}
}
