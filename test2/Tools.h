#ifndef TOOLS_H
#define TOOLS_H
#include <iostream>
#include <string>
#include <stack>
#include <algorithm>

namespace Wy
{
	class Tools
	{
	public:
		void LY_is_too_strong();
	};

	void Wy::Tools::LY_is_too_strong()
	{
		std::cout << "ÁõÔªºÜÇ¿" << std::endl;
	}

}

namespace Liuyuan
{
	using std::cin;
	using std::cout;
	using std::endl;
	using std::string;

	class Tools
	{
	public:
		//fflush cin istream
		static void Fflush();
		//get a value of specific kind
		template<class T> static T getData();
		//get a line of string
		static string getLine();
	};

	inline void Tools::Fflush()
	{
		cin.clear();
		cin.ignore(1024, '\n');
	}

	template<class T>
	static inline T Tools::getData()
	{
		T temp;
		cout << "Input a value: ";
		while (cin >> temp, cin.fail())
		{
			cout << "Input invalid value, input again: ";
			Fflush();
		}
		Fflush();
		return temp;
	}

	inline string Tools::getLine()
	{
		string temp;
		cout << "Input a line: ";
		std::getline(cin, temp);
		cin.clear();
		return temp;
	}
}


#endif