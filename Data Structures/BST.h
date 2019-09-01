#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <set>
#include <unordered_map>
#include <map>
#include <iostream>
#include <sstream>
#include <stack>
#include <ctime>
#include <queue>
#include <bitset>
#include <fstream>
#include <Windows.h>
#include <random>
#include <cstdio>

using namespace std;

static const auto io_speed_up = []() {
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);
	return 0;
}();

template<class K, class V>
struct Node {
	K key;
	V val;
	int N;
	Node<K, V> *left, *right;
	Node(K k, V v, int n = 1, Node<K, V> *p = nullptr, Node<K, V> *q = nullptr) :
		key(k), val(v), N(n), left(p), right(q) {}
};

template<class K, class V>
class BST {
public:
	void insert(K k, V v) { insert(k, v, root); }
	V & get(K k) { return get(k, root); }
	bool contains(K k) { return contain(k, root); }

	void erase(K k) { root = erase(k, root); }
	void printInOrder() { printInOrder(root); }

	bool empty() { return root; }
	int size() { return size(root); }
	V select(int rank) { return select(rank, root); }
private:
	Node<K, V> *root = nullptr;

	int size(Node<K, V> *p) { if (!p)return 0; return p->N; }
	V select(int rank, Node<K, V> *p);

	void insert(K k, V v, Node<K, V> *p);
	V & get(K k, Node<K, V> *p);
	Node<K, V> *contain(K k, Node<K, V> *p);

	Node<K, V>* erase(K k, Node<K, V> *p);
	Node<K, V>* eraseMin(Node<K, V>* p);

	void printInOrder(Node<K, V> *p);
	int refreshAll(Node<K, V> *p);
};


template<class K, class V>
V BST<K, V>::select(int rank, Node<K, V>* p)
{
	if (rank > size(p))return V();
	int t = size(p->left);

	if (rank <= t)return select(rank, p->left);
	else if (rank > t + 1) select(rank - t - 1, p->right);
	else return p->val;
}

template<class K, class V>
void BST<K, V>::insert(K k, V v, Node<K, V> *p)
{
	if (!root) {
		root = new Node<K, V>(k, v);
		return;
	}

	if (!p)throw("bug exsits!");

	if (k == p->key) {
		p->val = v;
		return;
	}
	else if (k < p->key) {
		if (!p->left) {
			p->left = new Node<K, V>(k, v);
			p->N = 1 + size(p->left) + size(p->right);
			return;
		}
		else insert(k, v, p->left);
	}
	else {
		if (!p->right) {
			p->right = new Node<K, V>(k, v);
			p->N = 1 + size(p->left) + size(p->right);
			return;
		}
		else insert(k, v, p->right);
	}
	p->N = 1 + size(p->left) + size(p->right);
}

template<class K, class V>
V & BST<K, V>::get(K k, Node<K, V>* p)
{
	Node<K, V>* tmp = contain(k, p);
	if (!tmp)throw ("The key did not exsit");
	return tmp->val;
}

template<class K, class V>
Node<K, V> *BST<K, V>::contain(K k, Node<K, V>* p)
{
	if (!p)return nullptr;
	if (k < p->key)return contain(k, p->left);
	if (k == p->key)return p;
	return contain(k, p->right);
}

int num = 0;

template<class K, class V>
Node<K, V>* BST<K, V>::erase(K k, Node<K, V>* p)
{
	if (!p)return nullptr;
	if (!contain(k, p))throw("did not exsit this key!");

	if (k < p->key)p->left = erase(k, p->left);
	else if (p->key < k)p->right = erase(k, p->right);
	else {
		if (!p->left) {
			Node<K, V>*tmp = p->right;
			delete p;
			return tmp;
		}
		else if (!p->right) {
			Node<K, V>*tmp = p->left;
			delete p;
			return tmp;
		}
		else {
			Node<K, V> *tmp = p->right;
			while (tmp->left)tmp = tmp->left;
			p->key = tmp->key;
			p->val = tmp->val;
			p->right = eraseMin(p->right);
		}
	}
	p->N = size(p->left) + 1 + size(p->right);
	return p;
	//refreshAll(root);
}

template<class K, class V>
Node<K, V>* BST<K, V>::eraseMin(Node<K, V>* p)
{
	if (!p->left) {
		Node<K, V>*tmp = p->right;
		delete p;
		return tmp;
	}
	p->left = eraseMin(p->left);
	p->N = size(p->left) + 1 + size(p->right);
	return p;
}

int tipr = 0;

template<class K, class V>
void BST<K, V>::printInOrder(Node<K, V>* p)
{
	if (!p)return;
	printInOrder(p->left);
	cout << ++tipr << " " << p->key << " " << p->val << endl;
	printInOrder(p->right);
}

template<class K, class V>
int BST<K, V>::refreshAll(Node<K, V>* p)
{
	if (!p)return 0;
	p->N = refreshAll(p->left) + refreshAll(p->right) + 1;
	return p->N;
}
