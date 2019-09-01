#pragma once
#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <ctime>
#include <set>
#include <queue>
#include <fstream>

using namespace std;

class WeightedQuickUF {  //QuickUnionFind ≤Â»Î∏¥‘”∂»O(lgn)
public:
	WeightedQuickUF(int n);
	~WeightedQuickUF() { delete[] id; delete[] sz; }
	int find(int i);
	bool connected(int p, int q) { return find(p) == find(q); }

	int count() { return Count; }
	void Union(int p, int q);

	void print();
	int calcDepth(int i);
	double calcAveDepth();
private:
	int *id;
	int *sz;
	int Count;
	int N;
};


WeightedQuickUF::WeightedQuickUF(int n) : N(n), Count(n)
{
	sz = new int[n];
	id = new int[n];
	for (int i = 0; i < N; ++i) {
		sz[i] = 1;
		id[i] = i;
	}
}

int WeightedQuickUF::find(int i)
{
	static int res[1000010];
	int res_n = 0;
	while (i != id[i]) {
		res[res_n++] = i;
		i = id[i];
	}
	for (int k = 0; k < res_n; k++)id[res[k]] = i;
	return i;
}

int WeightedQuickUF::calcDepth(int i)
{
	int s = 1;
	while (i != id[i]) {
		i = id[i];
		s++;
	}
	return s;
}

double WeightedQuickUF::calcAveDepth()
{
	double s = 0;
	for (int i = 0; i < N; ++i) {
		int k = calcDepth(i);
		s += k;
	}
	s /= N;
	cout << endl;
	return s;
}


void WeightedQuickUF::Union(int p, int q)
{
	int pId = find(p), qId = find(q);
	if (pId == qId)return;
	if (sz[pId] < sz[qId]) {
		sz[qId] += sz[pId];
		id[pId] = qId;
	}
	else {
		sz[pId] += sz[qId];
		id[qId] = id[pId];
	}
	Count--;
}

void WeightedQuickUF::print()
{
	for (int i = 0; i < N; ++i)
		cout << id[i] << " ";
	cout << endl;
}


