#pragma once
#ifndef CHAIN_H
#define CHAIN_H

#include "linearList.h"

template<class T>
struct chainNode
{
	T element;
	chainNode<T>* next;
	~chainNode() = default;
	chainNode() = default;
	chainNode(const T& el) : element(el), next(nullptr) {}
	chainNode(const T& el, chainNode<T>* ne) : element(el), next(ne) {}
};


template<class T>
class chain : public linearList<T>
{
public:
	chain();
	chain(const chain<T>&);
	~chain();

	bool empty() const { return listSize == 0; }
	int size() const { return listSize; }

	T& get(int theIndex) const override;
	int indexOf(const T &theElement)const override;
	void erase(int theIndex) override;
	void insert(int theIndex, const T &theElement) override;
	void output(ostream &out) override;

protected:
	chainNode<T>* firstNode;
	int arrayLength;
	int listSize;
	void checkIndex(int theIndex) const;
};




template<class T>
inline chain<T>::chain() : firstNode(nullptr), listSize(0) {}

template<class T>
inline chain<T>::chain(const chain<T> &theList) : listSize(theList.listSize)
{
	if (theList == 0)
	{
		firstNode = nullptr;
		return;
	}
	chainNode<T>* sourceNode = theList.firstNode;

	firstNode = new chainNode<T>*(sourceNode->element);

	chainNode<T>* targetNode = firstNode;
	sourceNode = sourceNode->next;

	while (sourceNode != nullptr)
	{
		targetNode->next = new chainNode<T>*(sourceNode->element);
		targetNode = targetNode->next;
		sourceNode = sourceNode->next;
	}
	targetNode->next = nullptr;
}

template<class T>
inline chain<T>::~chain()
{
	while (firstNode != nullptr)
	{
		chainNode<T>* nextNode = firstNode->next;
		delete firstNode;
		firstNode = nextNode;
	}
}

template<class T>
inline T & chain<T>::get(int theIndex) const
{
	checkIndex(theIndex);

	chainNode<T>* currentNode = firstNode;
	for (int i = 0; i < theIndex; ++i)
	{
		currentNode = currentNode->next;
	}
	return currentNode->element;
}

template<class T>
inline int chain<T>::indexOf(const T & theElement) const
{
	if (listSize == 0)return -1;
	chainNode<T>* currentNode = firstNode;
	for (int i = 0; i != listSize; ++i)
	{
		if (currentNode->element == theElement)return i;
		currentNode = currentNode->next;
	}
	return -1;
}

template<class T>
inline void chain<T>::erase(int theIndex)
{
	checkIndex(theIndex);

	if (theIndex == 0)
	{
		chainNode<T>* nextNode = firstNode->next;
		delete firstNode;
		firstNode = nextNode;
		--listSize;
		return;
	}

	chainNode<T>* currentNode = firstNode;
	for (int i = 0; i != theIndex - 1; ++i)
	{
		currentNode = currentNode->next;
	}

	chainNode<T>* nextNode = currentNode->next->next;
	delete (currentNode->next);
	currentNode->next = nextNode;
	--listSize;
}

template<class T>
inline void chain<T>::insert(int theIndex, const T & theElement)
{
	if (theIndex < 0 || theIndex > listSize)
	{
		ostringstream os;
		os << "Parameter theIndex = " << theIndex << "!" << endl;
		throw illegalIndex(os.str());
	}

	if (theIndex == 0)
	{
		chainNode<T>* nextNode = firstNode;
		firstNode = new chainNode<T>(theElement);
		firstNode->next = nextNode;
		++listSize;
		return;
	}

	chainNode<T>* currentNode = firstNode;
	for (int i = 0; i != theIndex - 1; ++i)
	{
		currentNode = currentNode->next;
	}
	chainNode<T>* nextNode = currentNode->next;
	currentNode->next = new chainNode<T>(theElement);
	currentNode->next->next = nextNode;
	++listSize;
}

template<class T>
inline void chain<T>::output(ostream & out)
{
	chainNode<T>* currentNode = firstNode;
	int i = 0;
	while (currentNode != nullptr)
	{
		out << i << ":	" << currentNode->element << endl;
		currentNode = currentNode->next;
		++i;
	}
}

template<class T>
inline void chain<T>::checkIndex(int theIndex) const
{
	if (theIndex < 0 || theIndex >= listSize)
	{
		ostringstream os;
		os << "Parameter theIndex = " << theIndex << "!" << endl;
		throw illegalIndex(os.str());
	}
}

#endif // !CHAIN_H
