#pragma once
#ifndef LINEAR_LIST_H
#define LINEAR_LIST_H

#include "errors.h"
#include <algorithm>
#include <sstream>
#include <iostream>
#include <fstream>
#include <numeric>

using namespace std;

template<class T>
class linearList
{
public:
	virtual ~linearList() {}
	virtual bool empty() const = 0;
	virtual int size() const = 0;
	virtual T& get(int theIndex) const = 0;
	virtual int indexOf(const T &theElement)const = 0;
	virtual void erase(int theIndex) = 0;
	virtual void insert(int theIndex, const T &theElement) = 0;
	virtual void output(ostream &out) = 0;
};

#endif // !LINEAR_LIST_H
