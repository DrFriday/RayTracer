#pragma once

#include <iostream>

class Test
{
private:
	int number_;

public:

	Test(int a)
		: number_(a)
	{
		std::cout << "Test initialized with number (" << number_ << ")" << std::endl;
	}
};

