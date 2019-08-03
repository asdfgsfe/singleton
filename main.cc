#include <iostream>
#include "singleton.h"

struct Test
{
	Test() 
	{
		std::cout << "Test()" << std::endl;
	}

	Test(const Test& other) 
	{
		std::cout << "Test(const Test& other)" << std::endl;
	}

	Test& operator=(const Test& other) 
	{
		std::cout << "Test(const Test& other)" << std::endl;
	}

	~Test()
	{
		std::cout << "~Test()" << std::endl;
	}
};

int main(void)
{
	const Test& t1 = Singleton<Test>::Instance();
	Test t2 = Singleton<Test>::Instance();

	return 0;
}
