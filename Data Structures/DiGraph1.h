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

class KosarajuSharirStronglyConnectedComponents;
class DiGragh;


class KosarajuSharirStronglyConnectedComponents {
public:
	KosarajuSharirStronglyConnectedComponents(DiGragh &g);
	~KosarajuSharirStronglyConnectedComponents() { delete id; delete marked; }
	KosarajuSharirStronglyConnectedComponents(const KosarajuSharirStronglyConnectedComponents &scc2);

	int count() const { return Count; }
	bool stronglyConnected(int v, int w) const { return id[v] == id[w]; }
	
private:
	int *id;
	int Count;
	int V;
	bool *marked;

	void dfs(DiGragh &g, int v);
};


class DiGragh {
public:
	DiGragh(int v);
	~DiGragh();
	DiGragh(const DiGragh &g2);

	void addEdge(int v, int w);
	set<int> *adj(int v) { return vertexes[v]; }
	bool connected(int v, int w, int time = 0);

	vector<int> bfsFind(int v, int w);
	bool dfsFind(int v, int w, vector<int> &res, vector<int> pre = {}, int ti = 0);

	vector<int> topoSort();
	bool findCircle();

	DiGragh DiReverse();
	KosarajuSharirStronglyConnectedComponents getSCC();

	friend class KosarajuSharirStronglyConnectedComponents;
private:
	int V;
	int E;
	set<int> **vertexes;

	void topoDfs(vector<int> &resVec, int i, bool *visited);  //底层实现
	bool findCircle(int v, bool *visited, bool *usin);
};

istream & operator>> (istream &is, DiGragh &g) {
	int m, n;
	is >> m >> n;
	g.addEdge(m, n);
	return is;
}

DiGragh::DiGragh(int v) : V(v), E(0)
{
	vertexes = new set<int> *[v];
	for (int i = 0; i < V; ++i) {
		vertexes[i] = nullptr;
	}
}

DiGragh::~DiGragh()
{
	for (int i = 0; i < V; ++i) {
		if (vertexes[i])delete vertexes[i];
	}
	delete[] vertexes;
}

inline DiGragh::DiGragh(const DiGragh & g2) : V(g2.V), E(0)
{
	vertexes = new set<int> *[V];
	for (int i = 0; i < V; ++i) {
		vertexes[i] = nullptr;
	}
	for (int i = 0; i < V; ++i) {
		if (g2.vertexes[i]) {
			for (int w : *g2.vertexes[i])
				addEdge(i, w);
		}
	}
}

void DiGragh::addEdge(int v, int w)
{
	if (v >= V || w >= V) throw("This gragh does not have that vertex!");
	
	if (!vertexes[v])vertexes[v] = new set<int>;
	vertexes[v]->insert(w);
	++E;
}

bool DiGragh::connected(int v, int w, int time)
{
	if (time > 10000)return 0;
	if (!vertexes[v])return false;
	if (vertexes[v]->count(w))return true;
	for (auto k : *vertexes[v]) {
		if (k == v)continue;
		if (connected(k, w, time + 1))return true;
	}
	return false;
}


bool DiGragh::dfsFind(int v, int w, vector<int> &res, vector<int> pre, int ti)
{
	pre.push_back(v);
	if (!vertexes[v])return 0;
	for (auto k : *vertexes[v]) {
		if (k == w) {
			pre.push_back(w);
			res = pre;
			return 1;
		}
	}
	if (ti > 1000)return 0;

	for (auto k : *vertexes[v]) {
		if (find(pre.begin(), pre.end(), k) != pre.end())continue;
		if (dfsFind(k, w, res, pre, ti + 1))return 1;
	}
	return 0;
}

bool DiGragh::findCircle()
{
	bool *visited = new bool[V];    //已经搜索过顶点的数组
	bool *usin = new bool[V];       //正在搜索的一条路径上的所有顶点的数组

	for (int i = 0; i < V; ++i) {   //初始化
		visited[i] = usin[i] = 0;
	}

	for (int i = 0; i < V; ++i) {
		if (visited[i])continue;             //每个顶点依次作为出发点开始搜索 搜索过的跳过
		if (findCircle(i, visited, usin)) {
			delete visited;                  //找到环了 直接return true
			delete usin;
			return 1;
		}
	}

	delete visited;
	delete usin;
	return 0;                               //没找到环
}

inline DiGragh DiGragh::DiReverse()
{
	DiGragh re(V);
	for (int i = 0; i < V; ++i) {
		if (vertexes[i]) {
			for (int w : *vertexes[i])
				re.addEdge(w, i);
		}
	}
	return re;
}

KosarajuSharirStronglyConnectedComponents DiGragh::getSCC()
{
	return KosarajuSharirStronglyConnectedComponents(*this);
}


bool DiGragh::findCircle(int v, bool *visited, bool *usin)
{
	if (visited[v])return 0;      //搜索过这个顶点，返回

	if (!vertexes[v])return 0;    //这个顶点没有指向其他顶点的边，返回

	usin[v] = 1;                  //把这个点置为搜索路径上的点

	for (int k : *vertexes[v]) {

		if (usin[k])return 1;              //有环，返回

		if (findCircle(k, visited, usin))  //递归调用
			return 1;
	}

	visited[v] = 1;             //将该节点置为搜索过的

	usin[v] = 0;                //该节点不再是搜索路径上的节点

	return 0;
}



vector<int> DiGragh::topoSort()
{
	if (findCircle())cout << "this gragh has circle!" << endl;
	//if (findCircle())return {};

	vector<int> res;                      //存储排序结果的向量
	bool *visited = new bool[V];          //存储各个顶点是否已经排过序的数组                                        

	for (int i = 0; i < V; ++i)           //初始化这两个数组
		visited[i] = 0;

	for (int i = 0; i < V; ++i)           //对每个（没排过序）的顶点进行深搜
		topoDfs(res, i, visited);

	delete[] visited;
	reverse(res.begin(), res.end());      //把后序反转成为逆后序
	return res;
}


void DiGragh::topoDfs(vector<int>& resVec, int i, bool *visited)
{
	if (visited[i])return;   //遇到已经加入序列的顶点 返回
	visited[i] = 1;         //将该顶点置为访问过的
	if (vertexes[i])
		for (int w : *vertexes[i])
			topoDfs(resVec, w, visited);//深搜递归调用

	resVec.push_back(i);    //结果序列中加入该顶点
	
}


struct state
{
	int toSearch;
	vector<int> preWay;
	state(int n, vector<int> vec = {}) : toSearch(n), preWay(vec) {}
};

vector<int> DiGragh::bfsFind(int v, int w)
{
	queue<state> que;
	que.push(state(v));

	while (!que.empty()) {

		state tmp = que.front();
		que.pop();

		if (!vertexes[tmp.toSearch])continue;
		tmp.preWay.push_back(tmp.toSearch);

		if (vertexes[tmp.toSearch]->count(w)) {
			tmp.preWay.push_back(w);
			return tmp.preWay;
		}

		for (int k : *vertexes[tmp.toSearch]) {
			if (find(tmp.preWay.begin(), tmp.preWay.end(), k) != tmp.preWay.end())
				continue;
			tmp.toSearch = k;
			que.push(tmp);
		}
	}
	return {};
}


KosarajuSharirStronglyConnectedComponents::KosarajuSharirStronglyConnectedComponents(DiGragh &g) : Count(0), V(g.V)
{
	id = new int[V];
	marked = new bool[V];
	for (int i = 0; i < V; ++i)
		marked[i] = 0;

	auto rg = g.DiReverse();
	auto vec = rg.topoSort();
/*
	for (int s : vec) {
		cout << s << " ";
	}
	cout << endl;
*/
	for (int s : vec) {
		if (!marked[s]) {
			dfs(g, s);
			++Count;
		}
	}
}

KosarajuSharirStronglyConnectedComponents::KosarajuSharirStronglyConnectedComponents(const KosarajuSharirStronglyConnectedComponents & scc2)
{
	Count = scc2.Count;
	marked = new bool[V];
	id = new int[V];
	for (int i = 0; i < V; ++i)id[i] = scc2.id[i];
}

void KosarajuSharirStronglyConnectedComponents::dfs(DiGragh & g, int v)
{
	marked[v] = 1;
	id[v] = Count;
	if (!g.vertexes[v])return;
	for (int w : *g.vertexes[v])
		if(!marked[w])
			dfs(g, w);
}

