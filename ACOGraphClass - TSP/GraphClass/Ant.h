#pragma once
#include <vector>
#include <random>
using namespace std;
enum class Status  { FORWARD, BACKWARD };
#include "Graph.h"
extern std::default_random_engine generator;
extern std::uniform_real_distribution<double> distribution;
extern std::uniform_int_distribution<int> int_distribution;// 
class Ant
{
	int label;
	double deltaTau = 1.0;
	int numCities, pathct = 0;
	double Pathlength=0;
	int start;
	int loc; // present location of Ant, ie vertex #
	vector<int> path;// path of Ant up to loc
	int past; // previous node.  
	vector<bool> visited; // true if in path list, ie have seen
	Status dir;// forward or backward

public:
	Ant()= delete;// not using default delete
	~Ant();
	Ant(int, Graph *,int);// start node ,  graph  and label this ant runs on
	//This function will move the ant to the next location based on the
	// ACO heuristic.  IE select a random edge using roulete wheel selection
	// of the edges tau value.  Remember that tau is its pheromone value
	void Move(Graph &,double,double);
	void Print();
	double GetPathLength(Graph& g);
	void Reset();
	void UpdatePheromoneTrail(Graph& g);
};

