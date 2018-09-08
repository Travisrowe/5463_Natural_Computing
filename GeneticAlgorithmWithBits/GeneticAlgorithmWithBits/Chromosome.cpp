#include "pch.h"
#include "Chromosome.h"

using namespace std;

Chromosome::Chromosome()
{
	RandomizeChrom();
	SetFitness();
}


Chromosome::~Chromosome()
{
	fitness = 0;
	chrom.reset();
}

//swap the bits after index pos with the bits from another Chromosome
//This function acts as a reproduction method. Parent A takes bits from 
//Parent B after index [pos]. Parent B gets the bits that Parent A just swapped.
//Thus, two children are born into a new generation.
void Chromosome::Crossover(Chromosome& parentB)
{
	double pCross = rand() / (double)RAND_MAX;
	if (pCross < .2)
	{
		return;
	}
	int pos = rand() % CHROM_SIZE;
	vector<int> tempA;
	vector<int> tempB;
	for (int i = pos; i < CHROM_SIZE; i++)
	{
		tempA.push_back(chrom[i]);
		tempB.push_back(parentB.chrom[i]);
	}
	for (int j = 0; j < tempA.size(); j++)
	{
		chrom[j + pos] = tempB[j];
		parentB.chrom[j + pos] = tempA[j];
	}
}

int Chromosome::GetFitness()
{
	return fitness;
}

void Chromosome::Print()
{
	for (int i = 0; i < CHROM_SIZE; i++)
	{
		cout << chrom[i];
	}
	cout << endl;
}

//Offers a chance for each bit to be "mutated" or flipped.
//Chance to mutate is .01.
//This function is to be called for each chromosome, once every generation
void Chromosome::Mutate()
{
	double r;
	double pmut = .01;
	for (int i = 0; i < CHROM_SIZE; i++)
	{
		r = rand() / (double)RAND_MAX;
		if (r < pmut)
		{
			chrom.flip(i);
		}
	}
}

//Fills the chromosome with random bits.
//This function is to be called once per run. It is only to establish the
//first generation.
void Chromosome::RandomizeChrom()
{
	for (int i = 0; i < CHROM_SIZE; i++)
	{
		int r = rand() % 2;
		chrom[i] = r;
	}
}

void Chromosome::SetFitness()
{
	fitness = 0;
	for (int i = 0; i < CHROM_SIZE; i++)
	{
		if (chrom[i] == 1)
			fitness++;
	}
}
