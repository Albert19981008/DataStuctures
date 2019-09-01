#pragma once


#pragma once
#include <algorithm>
#define stature(p) ((p) ? (p)->height : -1)

enum RBColour { RB_RED, RB_BLACK };

template<typename T>
struct BinNode
{
	T data;
	BinNode<T> *parent;
	BinNode<T> *leftChild, *rightChild;
	int height;
	int npl; // ×óÊ½¶Ñ
	RBColour colour;
	BinNode() : parent(nullptr), leftChild(nullptr), rightChild(nullptr),
		height(0), npl(1), colour(RB_RED) {}
	BinNode(T e, BinNode<T> *p = nullptr, BinNode<T> * lc = nullptr, BinNode<T> * rc = nullptr,
		int h = 0, int l = 1, RBColour col = RB_RED)
		: data(e), parent(p), leftChild(lc), rightChild(rc), height(h), npl(l), colour(col) {}


	int size();
	BinNode<T> * insertAsLc(const T &);
	BinNode<T> * insertAsRc(const T &);
	BinNode<T> * succ();

	bool operator< (BinNode const &bn) { return data < bn.data; }
	bool operator== (BinNode const &bn) { return data == bn.data; }
};

template<typename T>
inline int BinNode<T>::size()
{
	int s(1);
	if (leftChild)s += leftChild->size();
	if (rightChild)s += rightChild->size();
	return s;
}

template<typename T>
inline BinNode<T>* BinNode<T>::insertAsLc(const T & e)
{
	return leftChild = new BinNode<T>(e, this);
}

template<typename T>
inline BinNode<T>* BinNode<T>::insertAsRc(const T & e)
{
	return rightChild = new BinNode<T>(e, this);
}

#define isRoot(x) (!(x).parent)
#define hasParent(x) ((x).parent)
#define hasChild(x) ((x).leftChild || (x).rightChild)
#define hasBothChild(x) ((x).leftChild && (x).rightChild)
#define isLeaf(x) (! hasChild(x))

template <typename T>
class BinTree
{
protected:
	int _size;

	virtual int updateHeight(BinNode<T> *p);
	void updateHeightAbove(BinNode<T> *p);
public:
	BinNode<T> *root;
	int size() const { return _size; }
	bool empty() const { return !root; }
	//BinNode<T> *root() const { return root };
	BinNode<T> *insertAsRoot(const T &e);
	BinNode<T> *insertAsLC(BinNode<T> *p, const T &e);
	BinNode<T> *insertAsRC(BinNode<T> *p, const T &e);
	BinNode<T> *attachAsLC(BinNode<T> *p, BinTree<T> * &T);
	BinNode<T> *attachAsRC(BinNode<T> *p, BinTree<T> * &T);
};

template<typename T>
inline int BinTree<T>::updateHeight(BinNode<T>* p)
{
	return p->height = 1 + max(stature(p->leftChild), stature(p->rightChild));
}

template<typename T>
inline void BinTree<T>::updateHeightAbove(BinNode<T>* p)
{
	while (p)
	{
		updateHeight(p);
		p = p->parent;
	}
}

template<typename T>
inline BinNode<T>* BinTree<T>::insertAsRoot(const T & e)
{
	_size = 1;
	return root = new BinNode<T>(e);
}

template<typename T>
inline BinNode<T>* BinTree<T>::insertAsLC(BinNode<T>* p, const T & e)
{
	++_size;
	p->insertAsLc(e);
	updateHeightAbove(p);
	return p->leftChild;
}

template<typename T>
inline BinNode<T>* BinTree<T>::insertAsRC(BinNode<T>* p, const T & e)
{
	++_size;
	p->insertAsRc(e);
	updateHeightAbove(p);
	return p->rightChild;
}

template<typename T>
inline BinNode<T>* BinTree<T>::attachAsLC(BinNode<T>* p, BinTree<T>* &T)
{
	if (T->root)
	{
		p->leftChild = T->root;
		_size += T->_size;
		this->updateHeightAbove(p);
		p->leftChild->parent = p;
		T->root = nullptr;
		T->_size = 0;
		return p;
	}
}

template<typename T>
inline BinNode<T>* BinTree<T>::attachAsRC(BinNode<T>* p, BinTree<T>* &T)
{
	if (T->root)
	{
		p->rightChild = T->root;
		_size += T->_size;
		this->updateHeightAbove(p);
		p->rightChild->parent = p;
		T->root = nullptr;
		T->_size = 0;
		return p;
	}
}
