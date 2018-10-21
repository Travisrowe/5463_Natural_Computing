#include "Ant.h"

Ant::~Ant()
{
}


// s is where the ant begins his search at
Ant::Ant(int s, Graph * g,int lab)
{
	label = lab;
	numCities = g->GetSize();
	start=loc = s;
	visited.resize(numCities, false);
	visited[s] = true;
	dir = Status::FORWARD;
	past = -1;
	path.push_back(s);// s is the first item on the path
	Pathlength = 0;
}
void Ant::Move(Graph& g, double alpha, double beta)
{
		// select the next vertex using roulette selection
		vector<double> selectProb(g.GetSize(), 0.0);// used in roulette wheel selection
		double totalTauBetaSum = 0;
		int idx = 0;
		for (int vnum = 0; vnum < g.GetSize();vnum++) {
			
			if (!visited[vnum] && vnum!=loc) {// not visited  Remember first is len and second is tau
				double t = pow(g.AdjMat[loc][vnum].second, alpha)*pow(g.AdjMat[loc][vnum].first,beta);
				selectProb[idx] = t;
				totalTauBetaSum += t;
			}
			else {
				selectProb[idx] = 0.0;
			}
			idx++;
		}
		idx = 1;
		double sel = distribution(generator)*totalTauBetaSum;
		double sum = selectProb[0];
		while (sum < sel) {
			sum += selectProb[idx++];
		}
		// idx is now the randomly chosen vertex to move to
		past = loc;// save the previous one
		loc = idx-1;//loc is now the next selection
		path.push_back(loc);// add this vertex to the path
		visited[loc] = true;
		Pathlength += g.AdjMat[past][loc].first; // add on edge length
}

void Ant::Print() {
	cout << "Ant"<<label<<" Path("<<path.size()<<")=";
	for (auto l : path)cout << l << " ";
	cout << "   deltaTau :"<<deltaTau<< endl;
}


double Ant::GetPathLength(Graph& g) {
	if (path.size() != numCities)
		cout << "Error in Pathlength : path.size() is incorrect" << endl;
    // we have completed a tour !!
	// add on loop back to front length
	Pathlength += g.AdjMat[path[g.GetSize() - 1]][path[0]].first;
	//cout << "Ant:" << label << " len=" << Pathlength << " Path=";
	//for (auto x : path)cout << x << " ";
	//cout << endl;

	return Pathlength;
}


void Ant::Reset() {
	//start = path[0];
	path.clear();
	Pathlength = 0.0;
	int v = int_distribution(generator);// pick a new starting ant
	path.push_back(v);// start over and do it again
	visited.clear();
	visited.resize(numCities, false);
	visited[v] = true;
}

void Ant::UpdatePheromoneTrail(Graph& g)
{
	deltaTau = 1.0 / Pathlength;// inversely proportional to length
	for (int i = 0; i < path.size() - 1; i++) {
		g.AdjMat[path[i]][path[i + 1]].second += deltaTau;
	}
	// and the loop back tau value
	g.AdjMat[path[g.GetSize() - 1]][path[0]].second += deltaTau;
}