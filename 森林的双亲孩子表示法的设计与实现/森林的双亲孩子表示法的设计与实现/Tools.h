#pragma once
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

namespace Ly
{
	class Tools
	{
	public:
		template<class T>
		T getData();
	};

	template<class T>
	inline T Tools::getData()
	{
		T temp;
		std::cin >> temp;
		return T();
	}
}


