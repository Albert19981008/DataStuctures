#pragma once

#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <ctime>
#include "PQ.h"
#include <set>
#include <queue>
#include <fstream>
#include <iomanip>
#include <climits>
#include "UF.h"

using namespace std;


class weightedEdge;
class LazyPrimMST;
class InstantPrimMST;
class EdgeWeightedGraph;
class KruskalMST;

class weightedEdge {
public:
	weightedEdge(int V, int W, double wt);
	weightedEdge() = default;
	weightedEdge(const weightedEdge &) = default;
	int either() const { return v; };
	int other(int theVertex) const;
	double weight() const { return Weight; }
private:
	int v, w;
	double Weight;
};

weightedEdge::weightedEdge(int V, int W, double wt) : v(V), w(W), Weight(wt) {}

int weightedEdge::other(int theVertex) const
{
	if (theVertex == v)return w;
	else if (theVertex == w)return v;
	else throw("this vertex does not belong to this edge!");
}

bool operator<(const weightedEdge& e1, const weightedEdge& e2) {
	return e1.weight() < e2.weight();
}


bool operator>(const weightedEdge& e1, const weightedEdge& e2) {
	return e1.weight() > e2.weight();
}

class LazyPrimMST
{
public:
	LazyPrimMST(EdgeWeightedGraph &g, int root = 0);
	~LazyPrimMST();

	void visit(EdgeWeightedGraph &g, int v);

	double weight() { return weightCount; }
	vector<weightedEdge> edges;

	int V;
private:
	bool *marked;
	minPQ<weightedEdge> PQ;
	double weightCount;
};

class InstantPrimMST {
public:
	InstantPrimMST(EdgeWeightedGraph &g, int root = 0);
	~InstantPrimMST();

	void visit(EdgeWeightedGraph &g, int v);

	double weight() { return weightCount; }
	vector<weightedEdge> edges;

	int V;
private:
	bool *marked;
	minIndexPQ<weightedEdge> PQ;
	double weightCount;
};


class KruskalMST {
public:
	KruskalMST(EdgeWeightedGraph &g);
	~KruskalMST() = default;
	double getWeight() const { return count; }

	int V;
	vector<weightedEdge> edges;
private:
	WeightedQuickUF party;
	double count;
};



class EdgeWeightedGraph
{
public:
	EdgeWeightedGraph(int v);
	EdgeWeightedGraph(const LazyPrimMST& mst);
	~EdgeWeightedGraph();

	void addEdge(const weightedEdge &e);
	void addEdge(int v, int w, double wt);

	vector<weightedEdge> getAllEdges();
	LazyPrimMST getPrimMST(int root = 0) { return LazyPrimMST(*this, root); }
	KruskalMST getKruskalMST() { return KruskalMST(*this); }
	InstantPrimMST getInstantPrimMST() { return InstantPrimMST(*this); }

	friend class LazyPrimMST;
	friend class InstantPrimMST;
	friend class KruskalMST;
private:
	multiset<weightedEdge> **vertexes;
	int V, E;
};

InstantPrimMST::~InstantPrimMST()
{
	delete[] marked;
}


inline InstantPrimMST::InstantPrimMST(EdgeWeightedGraph & g, int root) : V(g.V), PQ(g.V)
{
	marked = new bool[g.V];
	
	for (int i = 0; i < g.V; ++i) {
		marked[i] = 0;
	}
	
	visit(g, root);

	while (!PQ.empty()) {
		weightedEdge minWeightedEdge = PQ.top();
		PQ.pop();

		int v = minWeightedEdge.either();
		int w = minWeightedEdge.other(v);

		if (marked[v] && marked[w])continue;

		edges.push_back(minWeightedEdge);
		//cout << minWeightedEdge.weight() << endl;
		weightCount += minWeightedEdge.weight();

		if (!marked[v])visit(g, v);
		if (!marked[w])visit(g, w);
	}
}


inline void InstantPrimMST::visit(EdgeWeightedGraph & g, int v)
{
	marked[v] = 1;
	if (g.vertexes[v]) {
		for (auto &e : *g.vertexes[v]) {
			if (!marked[e.other(v)]) {
				int w = e.other(v);
				if (PQ.contains(w)) {
					if (PQ.get(w).weight() > e.weight())
						PQ.change(w, e);
				}
				else PQ.insert(w, e);
			}
		}
	}
}


LazyPrimMST::LazyPrimMST(EdgeWeightedGraph & g, int root) : weightCount(0), V(g.V)
{
	marked = new bool[g.V];
	for (int i = 0; i < g.V; ++i)marked[i] = 0;
	visit(g, root);

	while (!PQ.empty()) {
		weightedEdge minWeightedEdge = PQ.top();
		PQ.pop();

		int v = minWeightedEdge.either();
		int w = minWeightedEdge.other(v);

		if (marked[v] && marked[w])continue;

		edges.push_back(minWeightedEdge);
		//cout << minWeightedEdge.weight() << endl;
		weightCount += minWeightedEdge.weight();
		if (!marked[v])visit(g, v);
		if (!marked[w])visit(g, w);
	}
}

LazyPrimMST::~LazyPrimMST()
{
	delete[] marked;
}

void LazyPrimMST::visit(EdgeWeightedGraph & g, int v)
{
	marked[v] = 1;
	if (g.vertexes[v]) {
		for (auto & k : *g.vertexes[v]) {
			//cout << "s: " << v << " " << k.other(v) << endl;
			if (!marked[k.other(v)])PQ.push(k);
		}
	}
}



KruskalMST::KruskalMST(EdgeWeightedGraph & g) : V(g.V), party(g.V), count(0)
{
	minPQ<weightedEdge> PQ(V);
	for (int i = 0; i < V; ++i) {
		if (g.vertexes[i]) {
			for (auto &k : *(g.vertexes[i])) {
				if (k.other(i) > i)PQ.push(k);
			}
		}
	}

	while (!PQ.empty() && edges.size() < V - 1) {
		auto minEdge = PQ.top();
		PQ.pop();
		int v = minEdge.either(), w = minEdge.other(v);
		if (party.connected(v, w))continue;
		party.Union(v, w);
		edges.push_back(minEdge);
		count += minEdge.weight();
	}
}




/*
int main()
{
	ifstream ifs("C:\\Users\\DELL\\Desktop\\largeEWG.txt");
	int V, E;
	ifs >> V >> E;
	cout << V << " " << E << endl;
	EdgeWeightedGraph g(V);
	int tmpV, tmpW;
	double weight;
	for (int i = 0; i < E; ++i) {
		ifs >> tmpV >> tmpW >> weight;
		g.addEdge(tmpV, tmpW, weight);
	}
	int timeReadFile = clock();
	cout << "文件读入时间: " << timeReadFile << endl;
	auto primMst = g.getinstantPrimMST();
	int timePrim = clock();
	cout << "prim时间: " << timePrim - timeReadFile << endl;
	auto KruskalMst = g.getKruskalMST();
	cout << "KruskalMst时间: " << clock() - timePrim << endl;
	cout << fixed << setprecision(10) << primMst.weight() << endl;
	cout << fixed << setprecision(10) << KruskalMst.getWeight() << endl;
	

	cout << clock() << endl;

	return 0;
}

*/



EdgeWeightedGraph::EdgeWeightedGraph(int v) : V(v), E(0)
{
	vertexes = new multiset<weightedEdge> *[v];
	for (int i = 0; i < V; ++i) {
		vertexes[i] = nullptr;
	}
}

EdgeWeightedGraph::EdgeWeightedGraph(const LazyPrimMST & mst) : V(mst.V), E(0)
{
	vertexes = new multiset<weightedEdge> *[V];
	for (int i = 0; i < V; ++i) {
		vertexes[i] = nullptr;
	}
	for (auto &k : mst.edges) {
		addEdge(k);
	}
}

EdgeWeightedGraph::~EdgeWeightedGraph()
{
	for (int i = 0; i < V; ++i) {
		if (vertexes[i])
			delete vertexes[i];
	}
	delete[] vertexes;
}

void EdgeWeightedGraph::addEdge(const weightedEdge & e)
{
	int v = e.either(), w = e.other(v);
	if (!vertexes[v])vertexes[v] = new multiset<weightedEdge>;
	if (!vertexes[w])vertexes[w] = new multiset<weightedEdge>;
	vertexes[v]->insert(e);
	vertexes[w]->insert(e);
}

void EdgeWeightedGraph::addEdge(int v, int w, double wt)
{
	if (!vertexes[v])vertexes[v] = new multiset<weightedEdge>;
	if (!vertexes[w])vertexes[w] = new multiset<weightedEdge>;
	vertexes[v]->emplace(v, w, wt);
	vertexes[w]->emplace(v, w, wt);
}


vector<weightedEdge> EdgeWeightedGraph::getAllEdges()
{
	vector<weightedEdge> res;
	for (int i = 0; i < V; ++i) {
		if (vertexes[i]) {
			for (auto & k : *vertexes[i])
				res.push_back(k);
		}
	}
	return res;
}