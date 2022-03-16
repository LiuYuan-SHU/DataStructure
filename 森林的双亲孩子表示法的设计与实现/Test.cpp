#include "Tools.h"

namespace Liuyuan
{
	void test_getData()
	{
		cout << Liuyuan::Tools::getData<int>() << endl;
		cout << Tools::getLine() << endl;
		cout << Tools::getLine() << endl;
	}
}

int main()
{
	Liuyuan::test_getData();
}