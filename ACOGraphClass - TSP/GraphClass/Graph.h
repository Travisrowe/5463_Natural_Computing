#pragma once
#include <iostream>
#include <vector>
//#include <functional> // stl::greater
using namespace std;
enum class type { DIRECTED, UNDIRECTED };
enum class color {WHITE,BLACK,GREY};
//const int INF = 1e9;
class Graph
{
	vector<vector<pair<double, double>>> AdjMat;// , vector<tuple< double, double>>(10)); 
	type dir;// Directed or Undirected
	int sz;
	friend class Ant;
public:
	Graph(int,type);
	~Graph();
	void Reset();
	int GetSize();
	void AddEdge(int from, int to, double wt);
	void Evaporate(double);
};

