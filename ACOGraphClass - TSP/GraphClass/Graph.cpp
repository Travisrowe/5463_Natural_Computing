#include "Graph.h"
// constructor : create a graph of with s nodes;
// This graph is implemented as a Adj list.
Graph::Graph(int s,type t)
{
	dir = t;
	sz = s;
	AdjMat.assign(s, vector < pair<double,double> >(s,make_pair(0.0,1.0)));// (wt,tau>
}


Graph::~Graph()
{
}

int Graph::GetSize()
{
	return sz;
}
// node numbers go from 0 to s-1;
// Loads both directions if type is UNDIRECTED
void Graph::AddEdge(int from, int to, double wt)
{
	AdjMat[from][to].first = wt;
	if (dir == type::UNDIRECTED)
		AdjMat[to][from].first = wt;
}

void Graph::Evaporate(double rho) {
	for(int i=0;i<sz;i++) 
		for(int j=0;j<sz;j++)
			AdjMat[i][j].second *= (1.0 - rho);
}

void Graph::Reset() {//Sets all tau values back to 1
	for (int i = 0; i<sz; i++)
		for (int j = 0; j<sz; j++)
			AdjMat[i][j].second =1.0;
}
