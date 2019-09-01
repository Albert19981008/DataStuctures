#pragma once

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <ctime>
#include <set>
#include <stack>
#include <queue>

using namespace std;

class Gragh {
public:
	Gragh(int v);
	~Gragh();

	void addEdge(int v, int w);
	set<int> *adj(int v) { return vertexs[v]; }
	bool connected(int v, int w, int time = 0);

	vector<int> bfsFind(int v, int w);
	bool dfsFind(int v, int w, vector<int> &res, vector<int> pre = {}, int ti = 0);

	bool findCircle(int v = -1, vector<int> = {});
private:
	int V;
	int E;
	set<int> **vertexs;
};

istream & operator>> (istream &is, Gragh &g) {
	int m, n;
	is >> m >> n;
	g.addEdge(m, n);
	return is;
}

Gragh::Gragh(int v) : V(v), E(0)
{
	vertexs = new set<int> *[v];
	for (int i = 0; i < V; ++i) {
		vertexs[i] = nullptr;
	}
}

Gragh::~Gragh()
{
	for (int i = 0; i < V; ++i) {
		if (vertexs[i])delete vertexs[i];
	}
}

void Gragh::addEdge(int v, int w)
{
	if (v >= V || w >= V) throw("");
	if (!vertexs[v])vertexs[v] = new set<int>;
	if (!vertexs[w])vertexs[w] = new set<int>;
	vertexs[v]->insert(w);
	vertexs[w]->insert(v);
	++E;
}

bool Gragh::connected(int v, int w, int time)
{
	if (time > 10000)return 0;
	if (!vertexs[v])return false;
	if (vertexs[v]->count(w))return true;
	for (auto k : *vertexs[v]) {
		if (k == v)continue;
		if (connected(k, w, time + 1))return 1;
	}
	return false;
}


bool Gragh::dfsFind(int v, int w, vector<int> &res, vector<int> pre, int ti)
{
	pre.push_back(v);
	if (!vertexs[v])return 0;
	for (auto k : *vertexs[v]) {
		if (k == w) {
			pre.push_back(w);
			res = pre;
			return 1;
		}
	}
	if (ti > 1000)return 0;

	for (auto k : *vertexs[v]) {
		if (find(pre.begin(), pre.end(), k) != pre.end())continue;
		if (dfsFind(k, w, res, pre, ti + 1))return 1;
	}
	return 0;
}

bool Gragh::findCircle(int v, vector<int> pre)
{
	bool b = 0;
	if (v == -1) {
		for (int i = 0; i < V; ++i) {
			if (findCircle(i, pre))b = 1;
		}
		return b;
	}
	if (!vertexs[v])return 0;

	pre.push_back(v);

	for (auto k : *vertexs[v]) {
		if (find(pre.begin(), pre.end(), k) != pre.end()) {
			for (int kk : pre)cout << kk << " ";
			cout << k << endl;
			continue;
		}
		if (findCircle(k, pre))b = 1;
	}
	return b;
}


struct state1
{
	int toSearch;
	vector<int> preWay;
	state1(int n, vector<int> vec = {}) : toSearch(n), preWay(vec) {}
};

vector<int> Gragh::bfsFind(int v, int w)
{
	queue<state1> que;
	que.push(state1(v));

	while (!que.empty()) {

		state1 tmp = que.front();
		que.pop();

		if (!vertexs[tmp.toSearch])continue;
		tmp.preWay.push_back(tmp.toSearch);

		if (vertexs[tmp.toSearch]->count(w)) {
			tmp.preWay.push_back(w);
			return tmp.preWay;
		}

		for (int k : *vertexs[tmp.toSearch]) {
			if (find(tmp.preWay.begin(), tmp.preWay.end(), k) != tmp.preWay.end())
				continue;
			tmp.toSearch = k;
			que.push(tmp);
		}
	}
	return {};
}