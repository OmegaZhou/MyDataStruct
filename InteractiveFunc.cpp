#include "InteractiveFunc.h"
#include <iostream>
#include <string>

void MyDataStruct::clearInvalidInput()
{
	std::string temp;
	std::cin.clear();
	std::getline(std::cin, temp);
}
