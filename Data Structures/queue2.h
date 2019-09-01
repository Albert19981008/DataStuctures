#pragma once

template<class T>
class queue2
{
public:
	virtual ~queue2() {}
	virtual bool empty() const = 0;
	virtual int size() const = 0;

	virtual T &front() const = 0;
	virtual T &back() const = 0;

	virtual void pop() = 0;

	virtual void push(const T &theElement) = 0;
};

template<class T>
class arrayQueue : public queue2<T>
{
public:
	arrayQueue(int initialCapacity = 10);
	~arrayQueue() { delete[] queueElements; };
	void doubleArrayLength();

	bool empty() const { return queueFront == queueBack; }
	int size() const { return (queueBack - queueFront + arrayLength) % arrayLength; }

	T &front() const { return queueElements[queueFront]; }
	T &back() const { return queueElements[queueBack - 1]; }

	void pop() override;
	void push(const T &theElement) override;
private:
	int queueFront, queueBack;
	int arrayLength;
	T *queueElements;
};

template<class T>
inline arrayQueue<T>::arrayQueue(int initialCapacity) : 
	arrayLength(initialCapacity), queueFront(0), queueBack(0)
{
	queueElements = new T[initialCapacity];
}

template<class T>
void arrayQueue<T>::doubleArrayLength()
{
	T *newPtr = new T[arrayLength * 2];
	int n = size();
	for (int i = 0; i < n; ++i)
	{
		newPtr[i] = queueElements[(queueFront + i) % arrayLength];
	}
	queueFront = 0;
	queueBack = n;
	delete[] queueElements;
	queueElements = newPtr;
	arrayLength *= 2;
}

template<class T>
inline void arrayQueue<T>::pop()
{
	/*if (empty())
	{
		cout << "empty Queue!" << endl;
		return;
	}*/
	queueElements[queueFront].~T();
	if (++queueFront == arrayLength)queueFront = 0;
}

template<class T>
inline void arrayQueue<T>::push(const T & theElement)
{
	if ((queueBack + 1) % arrayLength == queueFront)
	{
		doubleArrayLength();
	}
	queueElements[queueBack] = theElement;
	//queueBack = (queueBack + 1) % arrayLength;
	if (++queueBack == arrayLength)queueBack = 0;
	//queueElements[queueBack - 1] = theElement;
}

template<class T>
struct queueNode
{
	T element;
	queueNode<T>* next;
	~queueNode() = default;
	queueNode() = default;
	queueNode(const T& el) : element(el), next(nullptr) {}
	queueNode(const T& el, queueNode<T>* ne) : element(el), next(ne) {}
};

template<class T>
class linkedQueue : public queue2<T>
{
public:
	linkedQueue();
	~linkedQueue();

	bool empty() const { return queueSize == 0; }
	int size() const{ return queueSize; }

	T &front() const;
	T &back() const;

	void pop() override;
	void push(const T &theElement) override;
private:
	queueNode<T> *theFront;
	queueNode<T> *theBack;
	int queueSize;
};

template<class T>
inline linkedQueue<T>::linkedQueue() : theBack(nullptr), theFront(nullptr), queueSize(0)
{
}

template<class T>
inline linkedQueue<T>::~linkedQueue()
{
	if (theFront)
	{
		while (theFront != theBack)
		{
			queueNode<T> *tmp = theFront->next;
			delete theFront;
			theFront = tmp;
		}
		delete theBack;
	}
}

template<class T>
inline T & linkedQueue<T>::front() const
{
	return theFront->element;
}

template<class T>
inline T & linkedQueue<T>::back() const
{
	return theBack->element;
}

template<class T>
inline void linkedQueue<T>::pop()
{
	--queueSize;
	queueNode<T> *tmp = theFront->next;
	delete theFront;
	theFront = tmp;
}

template<class T>
inline void linkedQueue<T>::push(const T & theElement)
{
	if (empty())
	{
		theFront = theBack = new queueNode<T>(theElement);
		++queueSize;
		return;
	}
	theBack->next = new queueNode<T>(theElement);
	theBack = theBack->next;
	++queueSize;
}


