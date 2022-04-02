#ifndef STAY_TIME
#define STAY_TIME

#include <cassert>
#include <ctime>
#include <string>
#include <time.h>
#include <initializer_list>

using std::tm;
using std::mktime;
using std::string;
using std::initializer_list;

namespace liuyuan
{
	class stayTime
	{
	private:
		tm _time_entrance;
		tm _time_leave;
	public:
		// 构造函数
		// 传参按照 小时， 日， 月
		stayTime(int i_hour, int o_hour, int i_day, int o_day, int i_month = 1, int o_month = 1);
		// 一定要有6个参数
		stayTime(initializer_list<int> iList);
		// 拷贝函数
		stayTime(const stayTime& otherTime);

		// 判断两个人的时间是否重合
		bool operator&&(const stayTime& rightTime) const;
		// 计算停留的时间，返回秒数
		double stayTimeLength() { return difftime(mktime(&_time_entrance), mktime(&_time_leave)); }

		// 获取时间，按照 “month: day: hour” 返回
		// 如果isEntrance是true，返回进入时间
		// 否则返回离开时间
		string getTime(bool isEntrance);
		// 重新设置时间
		void setTime(bool isFirst, tm newTime) { isFirst ? (_time_entrance = newTime) : (_time_leave = newTime); }

		// 构造进出时间
		friend inline void construct_tm(tm& des, initializer_list<int> ilist);
	};

	// 将传入的tm结构体的小时、天、月份进行赋值，要求初始化列表的长度一定为3
	inline void construct_tm(tm &des, initializer_list<int> ilist )
	{
		// 检验传参完整性
		assert(ilist.size() == 3);		

		des.tm_hour = *(ilist.begin());
		des.tm_mday = *(ilist.begin() + 1);
		des.tm_mon = *(ilist.begin() + 2) - 1;
	}
	
	// 返回一个tm结构体指针，可以使用长度为0或3的初始化列表来为这个结构体赋值
	inline tm* construct_tm(initializer_list<int> ilist)
	{
		assert(ilist.size() == 0 || ilist.size() == 3);
		tm* temp;
		
		if (ilist.size() == 3)
		{
			temp = new tm;
			temp->tm_hour = *(ilist.begin());
			temp->tm_mday = *(ilist.begin() + 1);
			temp->tm_mon =  *(ilist.begin() + 2);
		}
		else
		{
			temp = nullptr;
		}
		
		return temp;
	}
}

#endif
