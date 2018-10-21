#include "Colony.h"
#include "Graph.h"


Colony::Colony(Graph &G,int a,int b)
{
	Gph = &G;
	alpha = a;
	beta = b;
}


Colony::~Colony()
{
}

void Colony::AddAnt(int loc, int lab) 
{
	colony.push_back(new Ant(loc, Gph,lab));// Add ant at loc to graph Gph
}

// Move all the ants on graph Gph one step
void Colony::MoveAnts(Graph & Gph)
{
	for (auto antPtr : colony) {
		antPtr->Move(Gph,alpha,beta);
	}
}
// Reset all the ants in the colony
void Colony::Reset() {
	for (auto antPtr : colony) {
		antPtr->Reset();//reset Ant
	}
}

void Colony::UpdatePheromoneTrails(Graph& g) {
	// update all the ants trails
	//for (auto antPtr : colony) {
	//	antPtr->UpdatePheromoneTrail(g);//apply to each ant for his solution
	//}

	// update the best ant only  . IE this is the elitism version of ASO
	colony[minAnt]->UpdatePheromoneTrail(g);
	//colony[minAnt]->Print();
}

double Colony::GetBestPathLength(Graph& g)
{
	double minLen = 10000000.0,len;
	minAnt = 0;// stored in colony
	for(int ant=0;ant<colony.size();ant++) {
		len=colony[ant]->GetPathLength(g);//apply to each ant for his solution
		if (len < minLen) {
			minLen = len;
			minAnt = ant;
		}
	}
	return minLen;
}