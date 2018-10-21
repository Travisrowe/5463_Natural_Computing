#pragma once
#include "Ant.h"
#include <vector>
#include "Graph.h"
class Colony
{
	Graph *Gph;
	vector<Ant*> colony;
	int numAnts;
	int minAnt = 0;
	int alpha, beta;
public:
	Colony()=delete;
	Colony(Graph&,int,int);//initialize colony
	~Colony();
	void MoveAnts(Graph&);
	void AddAnt(int,int);
	void Reset();
	void UpdatePheromoneTrails(Graph&);
	double GetBestPathLength(Graph&);
};

