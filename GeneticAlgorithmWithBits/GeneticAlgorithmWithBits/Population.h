#pragma once
#include "Chromosome.h"
class Population
{
private:
	const int POP_SIZE = 50;
	vector<Chromosome> population;
	int generation;

	int GetTotalFitness();
public:
	bool CheckConvergence();
	Population();
	Population(int);
	~Population();
	int GetAverageFitness();
	int GetGeneration();
	Chromosome RouletteSelection();
	void Print();
	void EvolveGeneration(Population&);
	void operator= (Population);
};

