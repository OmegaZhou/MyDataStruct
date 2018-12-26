#ifndef INTERACTIVE_FUNC_H_
#define INTERACTIVE_FUNC_H_
#include <iostream>
#include <string>

namespace MyDataStruct
{
	void clearInvalidInput();
}

void MyDataStruct::clearInvalidInput()
{
	std::string temp;
	std::cin.clear();
	std::getline(std::cin, temp);
}

#endif // !INTERACTIVE_FUNC_H_
