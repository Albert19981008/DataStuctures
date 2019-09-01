#pragma once


template<class T>
struct binaryTreeNode
{
	T element;
	binaryTreeNode<T> *leftChild, *rightChild;

	binaryTreeNode() : leftChild(nullptr), rightChild(nullptr) {}
	binaryTreeNode(const T &theElement) : element(theElement), leftChild(nullptr), rightChild(nullptr) {}
	binaryTreeNode(const T &theElement, binaryTreeNode<T> *l, binaryTreeNode<T> *r)
		: element(theElement), leftChild(l), rightChild(r) {}
};


template<class T>
class linkedBinaryTree
{
public:
	linkedBinaryTree() : root(nullptr), treeSize(0) {}
	~linkedBinaryTree() { erase(); }

	bool empty() const { return treeSize == 0; }
	int size() const { return treeSize; }
	binaryTreeNode<T> * &getRoot() { return root; }
	int height() const { return getHeight(root); }

	void swapTrees(binaryTreeNode<T> *tr);

	void preOrder(void(*theVisit)(binaryTreeNode<T> *))
	{
		visit = theVisit;
		preOrder(root);
	}

	void inOrder(void(*theVisit)(binaryTreeNode<T> *))
	{
		visit = theVisit;
		inOrder(root);
	}

	void postOrder(void(*theVisit)(binaryTreeNode<T> *))
	{
		visit = theVisit;
		postOrder(root);
	}
	void erase() { this->postOrder(dispose); root = nullptr; treeSize = 0; }

	static int getHeight(binaryTreeNode<T> *t)
	{
		if (!t)return 0;
		return 1 + max(getHeight(t->leftChild), getHeight(t->rightChild));
	}

private:
	binaryTreeNode<T> *root;
	int treeSize;
	
	void (*visit)(binaryTreeNode<T>*);
	void preOrder(binaryTreeNode<T> *t);
	void inOrder(binaryTreeNode<T> *t);
	void postOrder(binaryTreeNode<T> *t);
	static void dispose(binaryTreeNode<T> *t) { delete t; }
	
};

template<class T>
inline void linkedBinaryTree<T>::swapTrees(binaryTreeNode<T> *tr)
{
	if (!tr)return;
	swap(tr->leftChild, tr->rightChild);
	swapTrees(tr->leftChild);
	swapTrees(tr->rightChild);
}

template<class T>
inline void linkedBinaryTree<T>::preOrder(binaryTreeNode<T>* t)
{
	if (t)
	{
		visit(t);
		preOrder(t->leftChild);
		preOrder(t->rightChild);
	}
}

template<class T>
inline void linkedBinaryTree<T>::inOrder(binaryTreeNode<T>* t)
{
	if (t)
	{
		inOrder(t->leftChild);
		visit(t);
		inOrder(t->rightChild);
	}
}

template<class T>
inline void linkedBinaryTree<T>::postOrder(binaryTreeNode<T>* t)
{
	if (t)
	{
		postOrder(t->leftChild);
		postOrder(t->rightChild);
		visit(t);
	}
}
