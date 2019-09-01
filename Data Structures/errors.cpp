#include "stdafx.h"
#include "errors.h"

illegalValue::illegalValue() : message("Illegal value!") {}

illegalValue::illegalValue(char * s) : message(s){}

illegalValue::illegalValue(std::string s) : message(s) {}

void illegalValue::output()
{
	std::cout << message << std::endl;
}

illegalIndex::illegalIndex() : message("Illegal index!")
{
}

illegalIndex::illegalIndex(char * s) : message(s)
{
}

illegalIndex::illegalIndex(std::string s) : message(s)
{
}

void illegalIndex::output()
{
	std::cout << message << std::endl;
}
