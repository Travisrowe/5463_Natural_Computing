// GraphClass.cpp : This is the TSP version of the ACO algorithm.
// This works only on FULLY connected graphs at the moment.  Each ant
// will find a tour
// Note : at the moment the graph is read from stdin!!!
#include <iostream>
#include <string>
#include <random>
#include "Graph.h"
#include "Ant.h"
#include "Colony.h"
using namespace std;
int V=40;// number of vertices in graph. Should be set to match graph size .
// The above is a coding issue I need to address!!. Results from the global
// definition of the random functions below.  How can we fix this students?
std::default_random_engine generator(2);
std::uniform_real_distribution<double> distribution(0.0, 1.0);
std::uniform_int_distribution<int> int_distribution(0, V-1); 
	//cin >> size is below
	//we can pass size into a static distirbution function
int main()
{
	//std::default_random_engine generator(2);
	// Important parameters
	int numAnts = 50;
	int alpha = 1;  //this is the power value of the tau's
	int beta = -2; // this is the power value of the lengths
	int numSoln = 100;
	double rho = .7;// this is the evaporation factor. The algorithm is quite sensitive to this parameter
	double pathlen,minpathlen;

// read in edges and load the fully connected graph
	int size,f,t,minidx;
	double w;
	string dir;
	type d;
	cin >> dir >>size;
	//std::uniform_int_distribution<int> int_distribution(0, size- 1);// 
	if (dir == "U")d = type::UNDIRECTED;
	else d = type::DIRECTED;
    Graph Gph(size,d);
	while (cin >> f >> t>>w) {
		Gph.AddEdge(f, t, w);
	}
	cout << "start TSP search using "<<numAnts <<" ants with alpha="<<alpha<< " and with beta="<<beta<< endl;
    // Run the ants
	// The following loop will run the algorithm for multiple iterations.
	for (int iter = 0; iter < 1; iter++) {
		// Create colony of ants on this graph using alpha power
		Colony colony(Gph, alpha,beta);
		// Add some ants to the colony
		for (int i = 0; i < numAnts; i++) {
			int v = int_distribution(generator);
			// what could we do here differently?
			colony.AddAnt(v, i); //add ant on random vertex v with label i
		}

		// This is one iteration of the algorithm. Every ant finds a soln by traversing
		// the graph until V-1 cities are found
		minpathlen = 1000000.0;
		for (int i = 0; i < numSoln; i++) {
			for(int j=0;j<size-1;j++)
				colony.MoveAnts(Gph);// move every ant nine times to get a solution.
			pathlen = colony.GetBestPathLength(Gph);
			cout <<i<<": "<< pathlen << endl;// also sets bestant number so be used by Update command.
			if (pathlen < minpathlen) {
				minpathlen = pathlen;
				minidx = i;
			}
			// update the Pheromone trail for the best ant
			colony.UpdatePheromoneTrails(Gph);
			
			//reset the colony.  Sets ants to new locations and starts
			// to build a new solution path
			colony.Reset();
			// Evaporate the entire graph
			Gph.Evaporate(rho);  
		}
		cout << endl;
		cout << "***********************************************************"<<endl;
		cout << "Best result obtained has length " << minpathlen << endl;
		cout << "It was first discovered at iteration " << minidx << endl;
		cout << "***********************************************************"<<endl;
		Gph.Reset();// This starts everything over to collect new data
	}
	return 0;
}

