#pragma once


#include <iostream>

using namespace std;


template<class T>
class maxHeap {
public:
	maxHeap(int n = 10);
	~maxHeap();
	T top();
	void push(const T &el);
	void pop();
	void print();
	void init(T *arr, int n);
private:
	T *heap;
	int arraylength;
	int heapSize;
	bool isDynamic;
};

template<class T>
maxHeap<T>::maxHeap(int n) : heapSize(0), arraylength(n), isDynamic(true)
{
	heap = new T[n + 1];
}

template<class T>
maxHeap<T>::~maxHeap()
{
	if (heap && isDynamic)delete[] heap;
	heapSize = 0;
	arraylength = 10;
	heap = nullptr;
	isDynamic = 0;
}

template<class T>
T maxHeap<T>::top()
{
	if (!heap || heapSize <= 0)throw("");
	return heap[1];
}

template<class T>
void maxHeap<T>::push(const T & el)
{
	if (heapSize == arraylength) {
		arraylength *= 2;
		T * newHeap = new T[arraylength + 1];
		for (int i = 1; i <= heapSize; ++i) {
			newHeap[i] = heap[i];
		}
		delete[] heap;
		heap = newHeap;
	}
	int currentIndex = ++heapSize;
	while (currentIndex > 1 && heap[currentIndex / 2] < el) {
		heap[currentIndex] = heap[currentIndex / 2];
		currentIndex /= 2;
	}
	heap[currentIndex] = el;
}

template<class T>
void maxHeap<T>::pop()
{
	T tmp = heap[heapSize];
	heapSize--;
	int currentIndex = 1;
	while (true) {
		int childIndex = 2 * currentIndex;
		if (childIndex > heapSize)break;
		if (childIndex + 1 <= heapSize && heap[childIndex + 1] > heap[childIndex])++childIndex;
		if (tmp >= heap[childIndex])break;
		heap[currentIndex] = heap[childIndex];
		currentIndex = childIndex;
	}
	heap[currentIndex] = tmp;
}

template<class T>
void maxHeap<T>::print()
{
	for (int i = 1; i <= heapSize; ++i)cout << heap[i] << " ";
}

template<class T>
void maxHeap<T>::init(T * arr, int n)
{
	if (heap && isDynamic)delete[] heap;
	heap = arr;
	heapSize = n;
	isDynamic = false;

	for (int rootIndex = heapSize / 2; rootIndex >= 1; --rootIndex) {
		T rootElement = heap[rootIndex];
		int childIndex = rootIndex * 2;
		while (true) {
			if (childIndex >= heapSize)break;
			if (childIndex < heapSize && heap[childIndex] < heap[childIndex + 1])
				childIndex++;
			if (rootElement >= heap[childIndex])break;
			heap[childIndex / 2] = heap[childIndex];
			childIndex *= 2;
		}
		heap[childIndex / 2] = rootElement;
	}
}

template<class T>
void heapSort(T *arr, int n) {
	maxHeap<T> theHeap;
	theHeap.init(arr, n);
	for (int i = n - 1; i >= 1; --i) {
		T tmp = theHeap.top();
		theHeap.pop();
		arr[i + 1] = tmp;
	}
}
