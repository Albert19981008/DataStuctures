#pragma once

#include "UF.h"
#include "PQ.h"
#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <ctime>
#include <set>
#include <queue>
#include <fstream>
#include <climits>
#include <iomanip>

using namespace std;


static const auto io_speed_up = []() {
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);
	return 0;
}();


class DirectedWeightedEdge;
class WeightedDiGragh;
class DijkstraShortestPath;

class DirectedWeightedEdge
{
public:
	DirectedWeightedEdge(int f, int t, double w);
	DirectedWeightedEdge() = default;
	DirectedWeightedEdge(const DirectedWeightedEdge &) = default;
	~DirectedWeightedEdge() = default;

	int from() const { return v; }
	int to() const { return w; }
	double weight() const { return Weight; }

private:

	int v, w;
	double Weight;
};

DirectedWeightedEdge::DirectedWeightedEdge(int f, int t, double w) : v(f), w(t), Weight(w)
{
}

bool operator< (const DirectedWeightedEdge &l, const DirectedWeightedEdge &r) {
	return l.weight() < r.weight();
}

bool operator> (const DirectedWeightedEdge &l, const DirectedWeightedEdge &r) {
	return l.weight() > r.weight();
}

class AcyclicShortestPath {
public:
	AcyclicShortestPath(const WeightedDiGragh &g, int s);
	~AcyclicShortestPath() { delete[]edgeTo; delete[]distTo; }
	void relax(const WeightedDiGragh &g, int v);

	void printMindistToFile();
	void printDist();
private:
	int V;
	int st;
	DirectedWeightedEdge *edgeTo;
	double *distTo;
};


class DijkstraShortestPath {
public:
	DijkstraShortestPath(const WeightedDiGragh &g, int s);
	~DijkstraShortestPath() { delete[]edgeTo; delete[] distTo; }

	void printMindistTo();
	void printMindistToFile();
	vector<int> getPathTo(int);

private:
	void relax(const WeightedDiGragh &g, int v);
private:
	int V;
	int st;
	DirectedWeightedEdge *edgeTo;
	double *distTo;
	minIndexPQ<double> pq;
};

class WeightedDiGragh
{
public:
	WeightedDiGragh(int v);
	~WeightedDiGragh();

	void addEdge(int v, int w, double wt);

	vector<int> toPoSort() const;
	bool findCircle() const;

	int numOfVertexes() const { return V; }
	int numOfEdges() const { return E; }
	friend class DijkstraShortestPath;
	friend class AcyclicShortestPath;
private:
	void topoDfs(vector<int> &resVec, int i, bool *visited) const;  //�ײ�ʵ��
	bool findCircle(int v, bool *visited, bool *usin) const;

	int V, E;
	multiset<DirectedWeightedEdge> **vertexes;
};

AcyclicShortestPath::AcyclicShortestPath(const WeightedDiGragh & g, int s)
	: V(g.numOfVertexes()), st(s)
{
	edgeTo = new DirectedWeightedEdge[V];
	distTo = new double[V];
	for (int i = 0; i < V; ++i)distTo[i] = DBL_MAX;

	distTo[st] = 0;

	auto topo = g.toPoSort();
	cout << "ss:  " << topo[0] << endl;
	for (int w : topo) {
		this->relax(g, w);
	}
}

void AcyclicShortestPath::relax(const WeightedDiGragh & g, int v)
{
	if (!g.vertexes[v])return;
	for (auto &e : *g.vertexes[v]) {
		int w = e.to();
		if (distTo[w] > distTo[v] + e.weight()) {
			distTo[w] = distTo[v] + e.weight();
			edgeTo[w] = e;
		}
	}
}

void AcyclicShortestPath::printMindistToFile()
{
	ofstream ofs("C:\\Users\\DELL\\Desktop\\AcyclicSPRes.txt");
	for (int i = 0; i < V; ++i) {

		ofs << "distTo  " << i << ":  " << distTo[i] << endl;
	}
}

void AcyclicShortestPath::printDist()
{
	for (int i = 0; i < V; ++i) {
		if (distTo[i] > 2000000)continue;
		cout << "AcyclicdistTo  " << i << ":  " << distTo[i] << endl;
	}
}


DijkstraShortestPath::DijkstraShortestPath(const WeightedDiGragh & g, int s)
	: V(g.numOfVertexes()), st(s), pq(V)
{
	edgeTo = new DirectedWeightedEdge[V];
	distTo = new double[V];
	for (int i = 0; i < V; ++i)distTo[i] = DBL_MAX;
	distTo[st] = 0;

	pq.insert(s, 0.0);
	while (!pq.empty()) {
		int topKey = pq.getTopKey();
		pq.pop();
		relax(g, topKey);
	}
}

void DijkstraShortestPath::printMindistTo()
{
	for (int i = 0; i < V; ++i) {
		if (distTo[i] > 2000000)continue;
		cout << "DijkstradistTo  " << i << ":  " << distTo[i] << endl;
	}
}

void DijkstraShortestPath::printMindistToFile()
{
	ofstream ofs("C:\\Users\\DELL\\Desktop\\DijkstraSPRes.txt");
	for (int i = 0; i < V; ++i) {
		ofs << "distTo  " << i << ":  " << distTo[i] << endl;
	}
}


vector<int> DijkstraShortestPath::getPathTo(int w)
{
	if (w >= V)throw("");
	if (distTo[w] > 25400000)return {};
	vector<int> res;
	res.push_back(w);
	int from = w;
	while (from != st) {
		from = edgeTo[from].from();
		res.push_back(from);
	}
	reverse(res.begin(), res.end());
	return res;
}

void DijkstraShortestPath::relax(const WeightedDiGragh & g, int v)
{
	if (!g.vertexes[v])return;
	for (auto &e : *g.vertexes[v]) {
		int w = e.to();
		if (distTo[w] > distTo[v] + e.weight()) {

			if (pq.contains(w)) {
				pq.change(w, e.weight());
			}
			else {
				pq.insert(w, e.weight());
			}
			edgeTo[w] = e;
			distTo[w] = distTo[v] + e.weight();
		}
	}
}





WeightedDiGragh::WeightedDiGragh(int v) : V(v), E(0)
{
	vertexes = new multiset<DirectedWeightedEdge> *[V];
	for (int i = 0; i < V; ++i) {
		vertexes[i] = nullptr;
	}
}

WeightedDiGragh::~WeightedDiGragh()
{
	for (int i = 0; i < V; ++i)
		if (vertexes[i])
			delete vertexes[i];
	delete[] vertexes;
}

void WeightedDiGragh::addEdge(int v, int w, double wt)
{
	if (v < 0 || w < 0 || v >= V || w >= V)throw("b");
	//cout << "add: " << v << " " << w << " " << wt << endl;
	if (!vertexes[v])vertexes[v] = new multiset<DirectedWeightedEdge>;
	vertexes[v]->emplace(v, w, wt);
	++E;
}

vector<int> WeightedDiGragh::toPoSort() const
{
	if (findCircle())cout << "this gragh has circle!" << endl;
	//if (findCircle())return {};

	vector<int> res;                      //�洢������������
	bool *visited = new bool[V];          //�洢���������Ƿ��Ѿ��Ź��������                                        

	for (int i = 0; i < V; ++i)           //��ʼ������������
		visited[i] = 0;

	for (int i = 0; i < V; ++i)           //��ÿ����û�Ź��򣩵Ķ����������
		topoDfs(res, i, visited);

	delete[] visited;
	reverse(res.begin(), res.end());      //�Ѻ���ת��Ϊ�����
	return res;
}

bool WeightedDiGragh::findCircle() const
{
	bool *visited = new bool[V];    //�Ѿ����������������
	bool *usin = new bool[V];       //����������һ��·���ϵ����ж��������

	for (int i = 0; i < V; ++i) {   //��ʼ��
		visited[i] = usin[i] = 0;
	}

	for (int i = 0; i < V; ++i) {
		if (visited[i])continue;             //ÿ������������Ϊ�����㿪ʼ���� ������������
		if (findCircle(i, visited, usin)) {
			delete visited;                  //�ҵ����� ֱ��return true
			delete usin;
			return 1;
		}
	}

	delete visited;
	delete usin;
	return 0;
}

void WeightedDiGragh::topoDfs(vector<int>& resVec, int i, bool * visited) const
{
	if (visited[i])return;   //�����Ѿ��������еĶ��� ����
	visited[i] = 1;         //���ö�����Ϊ���ʹ���
	if (vertexes[i])
		for (auto &k : *vertexes[i])
			topoDfs(resVec, k.to(), visited);//���ѵݹ����

	resVec.push_back(i);    //��������м���ö���
}

bool WeightedDiGragh::findCircle(int v, bool * visited, bool * usin) const
{
	if (visited[v])return 0;      //������������㣬����

	if (!vertexes[v])return 0;    //�������û��ָ����������ıߣ�����

	usin[v] = 1;                  //���������Ϊ����·���ϵĵ�

	for (auto &k : *vertexes[v]) {
		int w = k.to();
		if (usin[w])return 1;              //�л�������

		if (findCircle(w, visited, usin))  //�ݹ����
			return 1;
	}

	visited[v] = 1;             //���ýڵ���Ϊ��������

	usin[v] = 0;                //�ýڵ㲻��������·���ϵĽڵ�

	return 0;
}

