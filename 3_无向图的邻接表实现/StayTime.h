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
		// ���캯��
		// ���ΰ��� Сʱ�� �գ� ��
		stayTime(int i_hour, int o_hour, int i_day, int o_day, int i_month = 1, int o_month = 1);
		// һ��Ҫ��6������
		stayTime(initializer_list<int> iList);
		// ��������
		stayTime(const stayTime& otherTime);

		// �ж������˵�ʱ���Ƿ��غ�
		bool operator&&(const stayTime& rightTime) const;
		// ����ͣ����ʱ�䣬��������
		double stayTimeLength() { return difftime(mktime(&_time_entrance), mktime(&_time_leave)); }

		// ��ȡʱ�䣬���� ��month: day: hour�� ����
		// ���isEntrance��true�����ؽ���ʱ��
		// ���򷵻��뿪ʱ��
		string getTime(bool isEntrance);
		// ��������ʱ��
		void setTime(bool isFirst, tm newTime) { isFirst ? (_time_entrance = newTime) : (_time_leave = newTime); }

		// �������ʱ��
		friend inline void construct_tm(tm& des, initializer_list<int> ilist);
	};

	// �������tm�ṹ���Сʱ���졢�·ݽ��и�ֵ��Ҫ���ʼ���б�ĳ���һ��Ϊ3
	inline void construct_tm(tm &des, initializer_list<int> ilist )
	{
		// ���鴫��������
		assert(ilist.size() == 3);		

		des.tm_hour = *(ilist.begin());
		des.tm_mday = *(ilist.begin() + 1);
		des.tm_mon = *(ilist.begin() + 2) - 1;
	}
	
	// ����һ��tm�ṹ��ָ�룬����ʹ�ó���Ϊ0��3�ĳ�ʼ���б���Ϊ����ṹ�帳ֵ
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
