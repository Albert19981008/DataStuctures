#pragma once
#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include "linearList.h"

template<class T>
class arrayList : public linearList<T>
{
public:
	arrayList(int initialCapacity = 10);
	arrayList(const arrayList<T>&);
	~arrayList() { delete[] elements; }
	arrayList<T>& operator=(const arrayList<T>&);

	bool empty() const { return listSize == 0; }
	int size() const { return listSize; }

	T& get(int theIndex) const override;
	int indexOf(const T &theElement)const override;
	void erase(int theIndex) override;
	void insert(int theIndex, const T &theElement) override;
	void output(ostream &out) override;
	T& operator[](int i);

protected:
	T * elements;
	int arrayLength;
	int listSize;
	void checkIndex(int theIndex) const;
};


template<class T>
inline arrayList<T>::arrayList(int initialCapacity)
{

	if (initialCapacity < 1)
	{
		ostringstream os;
		os << "Initial Capacity = " << initialCapacity << " must be > 0!" << endl;
		throw illegalValue(os.str());
	}

	arrayLength = initialCapacity;
	elements = new T[arrayLength];
	listSize = 0;
}

template<class T>
inline arrayList<T>::arrayList(const arrayList<T>&theList)
{
	listSize = theList.listSize;
	arrayLength = theList.arrayLength;
	elements = new T[arrayLength];
	copy(theList.elements, theList.elements + listSize, elements);
}


template<class T>
inline arrayList<T>& arrayList<T>::operator=(const arrayList<T>&t2)
{
	listSize = t2.listSize;
	arrayLength = t2.arrayLength;
	this->elements = new T[arrayLength];
	for (int i = 0; i < listSize; ++i)elements[i] = t2.get(i);
	return *this;
}


template<class T>
inline T & arrayList<T>::get(int theIndex) const
{
	checkIndex(theIndex);
	return elements[theIndex];
}

template<class T>
inline int arrayList<T>::indexOf(const T & theElement) const
{
	int theIndex = (find(elements, elements + listSize, theElement)) - elements;
	return ((theIndex == listSize) ? -1 : theIndex);
}

template<class T>
inline void arrayList<T>::erase(int theIndex)
{
	checkIndex(theIndex);

	copy(elements + theIndex + 1, elements + listSize, elements + theIndex);
	elements[--listSize].~T();
}

template<class T>
inline void arrayList<T>::insert(int theIndex, const T & theElement)
{

	if (theIndex < 0 || theIndex > listSize)
	{
		ostringstream os;
		os << "Parameter theIndex = " << theIndex << "!" << endl;
		throw illegalIndex(os.str());
	}
	if (listSize == arrayLength)
	{
		T * p = new T[arrayLength * 2];
		arrayLength *= 2;
		copy(elements, elements + listSize, p);
		elements = p;
	}
	copy_backward(elements + theIndex, elements + listSize, elements + theIndex + 1);

	elements[theIndex] = theElement;
	++listSize;
}

template<class T>
inline void arrayList<T>::output(ostream & out)
{
	for (int i = 0; i != listSize; ++i)
	{
		//out << elements[i] << endl;
	}
}

template<class T>
inline T & arrayList<T>::operator[](int i)
{
	return elements[i];
}

template<class T>
inline void arrayList<T>::checkIndex(int theIndex) const
{

	if (theIndex < 0 || theIndex >= listSize)
	{
		ostringstream os;
		os << "Parameter theIndex = " << theIndex << "!" << endl;
		throw illegalIndex(os.str());
	}
}

#endif // !ARRAY_LIST_H
