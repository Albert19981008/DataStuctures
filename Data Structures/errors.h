#pragma once
#ifndef ERRORS_H
#define ERRORS_H

#include <string>
#include <iostream>
class illegalValue
{
public:
	illegalValue();
	illegalValue(char *s);
	illegalValue(std::string s);
	void output();
private:
	std::string message;
};

class illegalIndex
{
public:
	illegalIndex();
	illegalIndex(char *s);
	illegalIndex(std::string s);
	void output();
private:
	std::string message;
};


#endif // !ERRORS_H
