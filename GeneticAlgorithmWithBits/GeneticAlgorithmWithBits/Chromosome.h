#pragma once
#include <iostream>
#include <vector>
#include <bitset>
#include <stdlib.h>

using namespace std;

class Chromosome
{
private:
	const int CHROM_SIZE = 40;
	bitset<40> chrom;
	int fitness;

	void SetFitness();
	void RandomizeChrom();
public:
	Chromosome();
	~Chromosome();
	void Crossover(Chromosome&);
	void Mutate();
	int GetFitness();
	void Print();
	void operator= (Chromosome);
	int GetChromSize();
};

