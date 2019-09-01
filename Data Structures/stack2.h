#pragma once

#include "arrayList.h"

template<class T>
class stack2
{
public:
	virtual ~stack2() {};
	virtual bool empty() const = 0;
	virtual int size() const = 0;
	virtual T &top() = 0;
	virtual void pop() = 0;
	virtual void push(const T &theElement) = 0;
};


template<class T>
class derivedArrayStack : private arrayList<T>, public stack2<T>
{
public:
	derivedArrayStack(int initialCapacity = 10) : arrayList<T>(initialCapacity) {}
	bool empty() const { return arrayList<T>::empty(); }
	int size() const { return arrayList<T>::size(); }
	T &top() { return arrayList<T>::get(arrayList<T>::size() - 1); }
	void pop() { arrayList<T>::erase(arrayList<T>::size() - 1); }
	void push(const T &theElement) { arrayList<T>::insert(arrayList<T>::size(), theElement); }
	int find(const T &t2);
};

template<class T>
inline int derivedArrayStack<T>::find(const T & el)
{
	for (int i = 0; i < this->listSize; ++i)if (el == this->elements[i])return i;
	return -1;
}
template<class T>
class arrayStack : public stack2<T>
{
public:
	arrayStack(int initialCapacity = 10);
	~arrayStack() { delete[] stackElements; }
	bool empty() const { return stackTop == -1; }
	int size() const { return stackTop + 1; }
	T &top() override { return stackElements[stackTop]; }
	void pop() override{ stackElements[stackTop--].~T(); }
	void push(const T &theElement) override;
private:
	int stackTop;
	int arrayLenth;
	T *stackElements;
};

template<class T>
inline arrayStack<T>::arrayStack(int initialCapacity)
	: stackTop(-1), arrayLenth(initialCapacity)
{
	stackElements = new T[initialCapacity];
}

template<class T>
inline void arrayStack<T>::push(const T & theElement)
{
	if (stackTop == arrayLenth - 1)
	{
		T *newPtr = new T[arrayLenth * 2];
		for (int i = 0; i <= stackTop; ++i)newPtr[i] = stackElements[i];
		delete[] stackElements;
		stackElements = newPtr;
		arrayLenth *= 2;
	}
	stackElements[++stackTop] = theElement;
}


template<class T>
struct linkedStackNode
{
	T element;
	linkedStackNode<T>* next;
	~linkedStackNode() = default;
	linkedStackNode() = default;
	linkedStackNode(const T& el) : element(el), next(nullptr) {}
	linkedStackNode(const T& el, linkedStackNode<T>* ne) : element(el), next(ne) {}
};


template<class T>
class linkedStack : public stack2<T>
{
public:
	linkedStack(int initialCapacity = 10) : stackTop(nullptr), stackSize(0) {}
	~linkedStack();
	bool empty() const { return stackSize == 0; }
	int size() const { return stackSize; }
	T &top() override { return stackTop->element; }
	void pop() override;
	void push(const T &theElement) override;
private:
	linkedStackNode<T> *stackTop;
	int stackSize;
};

template<class T>
inline linkedStack<T>::~linkedStack()
{
	while (stackTop)
	{
		linkedStackNode<T> * p = stackTop->next;
		delete stackTop;
		stackTop = p;
	}
}

template<class T>
inline void linkedStack<T>::pop()
{
	linkedStackNode<T> * p = stackTop->next;
	delete stackTop;
	stackTop = p;
	--stackSize;
}

template<class T>
inline void linkedStack<T>::push(const T & theElement)
{
	stackTop = new linkedStackNode<T>(theElement, stackTop);
	++stackSize;
}
