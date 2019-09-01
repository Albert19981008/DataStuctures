#pragma once


template<class T>
class maxPQ {
public:
	maxPQ(int n = 10);

	void push(const T &theElement);
	void pop();
	T top() const { return elements[1]; }

	bool empty() const { return heapSize == 0; }
	int size() const { return heapSize; }
private:
	void exch(int i, int j);
	void swim(int index);
	void sink(int index);
private:
	T * elements;
	int maxSize;
	int heapSize;
};

template<class T>
inline maxPQ<T>::maxPQ(int n) : maxSize(n), heapSize(0)
{
	elements = new T[maxSize + 1];
}

template<class T>
inline void maxPQ<T>::push(const T & theElement)
{
	if (heapSize == maxSize) {
		T *newArray = new T[maxSize * 2 + 1];
		for (int i = 1; i <= heapSize; ++i) {
			newArray[i] = elements[i];
		}
		delete[] elements;
		elements = newArray;
		maxSize *= 2;
	}
	elements[++heapSize] = theElement;
	swim(heapSize);
}

template<class T>
inline void maxPQ<T>::pop()
{
	exch(1, heapSize--);
	sink(1);
}

template<class T>
inline void maxPQ<T>::exch(int i, int j)
{
	T tmp = elements[i];
	elements[i] = elements[j];
	elements[j] = tmp;
}

template<class T>
inline void maxPQ<T>::swim(int index)
{
	while (index > 1) {
		if (elements[index / 2] < elements[index]) {
			exch(index / 2, index);
			index /= 2;
		}
		else break;
	}
}

template<class T>
inline void maxPQ<T>::sink(int index)
{
	while (index * 2 <= heapSize) {
		int childIndex = index * 2;
		if (childIndex < heapSize && elements[childIndex] < elements[childIndex + 1])
			childIndex++;
		if (elements[childIndex] < elements[index])break;
		exch(index, childIndex);
		index = childIndex;
	}
}



template<class T>
class minPQ {
public:
	minPQ(int n = 10);

	void push(const T &theElement);
	void pop();
	T top() const { return elements[1]; }

	bool empty() const { return heapSize == 0; }
	int size() const { return heapSize; }
private:
	void exch(int i, int j);
	void swim(int index);
	void sink(int index);
private:
	T * elements;
	int maxSize;
	int heapSize;
};

template<class T>
inline minPQ<T>::minPQ(int n) : maxSize(n), heapSize(0)
{
	elements = new T[maxSize + 1];
}

template<class T>
inline void minPQ<T>::push(const T & theElement)
{
	if (heapSize == maxSize) {
		T *newArray = new T[maxSize * 2 + 1];
		for (int i = 1; i <= heapSize; ++i) {
			newArray[i] = elements[i];
		}
		delete[] elements;
		elements = newArray;
		maxSize *= 2;
	}
	elements[++heapSize] = theElement;
	swim(heapSize);
}

template<class T>
inline void minPQ<T>::pop()
{
	exch(1, heapSize--);
	sink(1);
}

template<class T>
inline void minPQ<T>::exch(int i, int j)
{
	T tmp = elements[i];
	elements[i] = elements[j];
	elements[j] = tmp;
}

template<class T>
inline void minPQ<T>::swim(int index)
{
	while (index > 1) {
		if (elements[index / 2] > elements[index]) {
			exch(index / 2, index);
			index /= 2;
		}
		else break;
	}
}

template<class T>
inline void minPQ<T>::sink(int index)
{
	while (index * 2 <= heapSize) {
		int childIndex = index * 2;
		if (childIndex < heapSize && elements[childIndex] > elements[childIndex + 1])
			childIndex++;
		if (elements[childIndex] > elements[index])break;
		exch(index, childIndex);
		index = childIndex;
	}
}




template<class T>
class maxIndexPQ
{
public:
	maxIndexPQ(int capacity = 10);
	~maxIndexPQ();

	bool contains(int i) const { return qp[i] != -1; }
	int size() const { return heapSize; }
	bool empty() const { return heapSize == 0; }
	T get(int k)const { return elements[k + 1]; }

	void insert(int key, const T &theElement);
	void change(int key, const T &theElement);

	void push(int key, const T &theElement);
	T top() const { return elements[pq[1]]; }
	void pop();
private:
	void exch(int i, int j);
	void swim(int index);
	void sink(int index);
private:
	int *pq;
	int *qp;
	T *elements;
	int maxSize;
	int heapSize;
};

template<class T>
maxIndexPQ<T>::maxIndexPQ(int capacity) : maxSize(capacity), heapSize(0)
{
	pq = new int[maxSize + 1];
	qp = new int[maxSize + 1];
	elements = new T[maxSize + 1];
	for (int i = 0; i <= maxSize; ++i)qp[i] = -1;
}

template<class T>
maxIndexPQ<T>::~maxIndexPQ()
{
	delete[] pq;
	delete[] qp;
	delete[] elements;
}

template<class T>
inline void maxIndexPQ<T>::insert(int key, const T & theElement)
{
	if (key >= maxSize) {
		throw ("overFlow!");
	}

	key++; //使得关联的整数可以为0

	if (qp[key] != -1) {
		throw ("");
	}

	elements[key] = theElement;
	pq[++heapSize] = key;
	qp[key] = heapSize;
	swim(heapSize);
}

template<class T>
inline void maxIndexPQ<T>::change(int key, const T & theElement)
{
	if (key >= maxSize) {
		throw ("overFlow!");
	}

	key++;
	if (qp[key] == -1) {
		throw ("");
	}
	elements[key] = theElement;
	swim(qp[key]);
	sink(qp[key]);
}

template<class T>
inline void maxIndexPQ<T>::push(int key, const T & theElement)
{
	if (key >= maxSize) {
		throw ("overFlow!");
	}

	if (contains(key))change(key, theElement);
	else insert(key, theElement);
}

template<class T>
inline void maxIndexPQ<T>::pop()
{
	exch(heapSize--, 1);
	sink(1);

	qp[pq[heapSize + 1]] = -1;
}

template<class T>
inline void maxIndexPQ<T>::exch(int i, int j)
{
	int tmp = pq[i];
	pq[i] = pq[j];
	pq[j] = tmp;
	//swap(qp, pq[parent], pq[child]);
	tmp = qp[pq[i]];
	qp[pq[i]] = qp[pq[j]];
	qp[pq[j]] = tmp;
}

template<class T>
inline void maxIndexPQ<T>::swim(int index)
{
	while (index > 1) {
		if (elements[pq[index / 2]] < elements[pq[index]]) {
			exch(index / 2, index);
			index /= 2;
		}
		else break;
	}
}

template<class T>
inline void maxIndexPQ<T>::sink(int index)
{
	while (index * 2 <= heapSize) {
		int childIndex = index * 2;
		if (childIndex < heapSize && elements[pq[childIndex]] < elements[pq[childIndex + 1]])
			childIndex++;
		if (elements[pq[childIndex]] < elements[pq[index]])break;
		exch(index, childIndex);
		index = childIndex;
	}
}



template<class T>
class minIndexPQ
{
public:
	minIndexPQ(int capacity = 10);
	~minIndexPQ();

	bool contains(int i) const { return (qp[i + 1] != -1); }
	int size() const { return heapSize; }
	bool empty() const { return (heapSize == 0); }
	T get(int k)const { return elements[k + 1]; }
	int getTopKey() const { return pq[1] - 1; }

	void insert(int key, const T &theElement);
	void change(int key, const T &theElement);

	void push(int key, const T &theElement);
	T top() const { return elements[pq[1]]; }
	void pop();
private:
	void exch(int i, int j);
	void swim(int index);
	void sink(int index);
private:
	int *pq;
	int *qp;
	T *elements;
	int maxSize;
	int heapSize;
};

template<class T>
minIndexPQ<T>::minIndexPQ(int capacity) : maxSize(capacity), heapSize(0)
{
	pq = new int[maxSize + 1];
	qp = new int[maxSize + 1];
	elements = new T[maxSize + 1];
	for (int i = 0; i <= maxSize; ++i)qp[i] = -1;
}

template<class T>
minIndexPQ<T>::~minIndexPQ()
{
	delete[] pq;
	delete[] qp;
	delete[] elements;
}

template<class T>
inline void minIndexPQ<T>::insert(int key, const T & theElement)
{
	if (key >= maxSize) {
		throw ("overFlow!");
	}

	key++; //使得关联的整数可以为0

	if (qp[key] != -1) {
		throw ("");
	}
	//cout << "inserting:            " << key - 1 << endl;
	elements[key] = theElement;
	pq[++heapSize] = key;
	qp[key] = heapSize;
	swim(heapSize);
	//cout << "insertingContains5:            " << contains(5) << endl;
}

template<class T>
inline void minIndexPQ<T>::change(int key, const T & theElement)
{
	if (key >= maxSize) {
		throw ("overFlow!");
	}

	key++;     //使得关联的整数可以为0

	if (qp[key] == -1) {
		throw ("");
	}
	elements[key] = theElement;
	swim(qp[key]);
	sink(qp[key]);
}

template<class T>
inline void minIndexPQ<T>::push(int key, const T & theElement)
{
	if (key >= maxSize) {
		throw ("overFlow!");
	}

	if (contains(key))change(key, theElement);
	else insert(key, theElement);
}

template<class T>
inline void minIndexPQ<T>::pop()
{
	exch(heapSize--, 1);
	sink(1);
	//cout << "pop: " << pq[heapSize + 1] - 1 << endl;
	qp[pq[heapSize + 1]] = -1;
}

template<class T>
inline void minIndexPQ<T>::exch(int i, int j)
{
	int tmp = pq[i];
	pq[i] = pq[j];
	pq[j] = tmp;

	tmp = qp[pq[i]];
	qp[pq[i]] = qp[pq[j]];
	qp[pq[j]] = tmp;
}

template<class T>
inline void minIndexPQ<T>::swim(int index)
{
	while (index > 1) {
		if (elements[pq[index / 2]] > elements[pq[index]]) {
			exch(index / 2, index);
			index /= 2;
		}
		else break;
	}
}

template<class T>
inline void minIndexPQ<T>::sink(int index)
{
	while (index * 2 <= heapSize) {
		int childIndex = index * 2;
		if (childIndex < heapSize && elements[pq[childIndex]] > elements[pq[childIndex + 1]])
			childIndex++;
		if (elements[pq[childIndex]] > elements[pq[index]])break;
		exch(index, childIndex);
		index = childIndex;
	}
}
