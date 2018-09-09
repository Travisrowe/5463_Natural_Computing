#include "pch.h"
#include "Population.h"

bool Population::CheckConvergence()
{
	for (int i = 0; i < POP_SIZE; i++)
	{
		if (population[i].GetFitness() == 20)
			return true;
	}
	return false;
}

void Population::EvolveGeneration(Population& nextGen)
{
	while (nextGen.population.size() < POP_SIZE)
	{
		Chromosome a = RouletteSelection();
		Chromosome b = RouletteSelection();
		a.Crossover(b);
		a.Mutate();
		b.Mutate();
		nextGen.population.push_back(a);
		nextGen.population.push_back(b);
	}
}

int Population::GetAverageFitness()
{
	return GetTotalFitness() / POP_SIZE;
}

int Population::GetGeneration()
{
	return generation;
}

int Population::GetTotalFitness()
{
	int totFitness = 0;
	for (int i = 0; i < POP_SIZE; i++)
	{
		totFitness += population[i].GetFitness();
	}
	return totFitness;
}

void Population::operator= (Population newGen)
{
	for (int i = 0; i < POP_SIZE; i++)
	{
		population[i] = newGen.population[i];
	}
	this->generation = newGen.generation;
}

void Population::Print()
{
	cout << population.size() << endl;
	for (int i = 0; i < POP_SIZE; i++)
	{
		population[i].Print();
	}
}

//By default, this fills a population with random Chromosomes
Population::Population()
{
	generation = 1;

	population.reserve(POP_SIZE);
	for (int i = 0; i < POP_SIZE; i++)
	{
		Chromosome x;
		population.push_back(x);
	}
}

//This creates an empty population, but adjusts the generation number
Population::Population(int gen)
{
	generation = gen;
}

Population::~Population()
{
	population.clear();
}

/*Returns a parent Chromosome to be used in Crossover.
 *
 *This selection method gives each Chromosome a section of a roulette wheel
 *equal to that Chromosome's fitness / total population fitness. In this
 *way, Chromosome's with higher fitness have a higher chance of being
 *selected for crossover (reproduction).
 */
Chromosome Population::RouletteSelection()
{
	int totFitness = GetTotalFitness();
	int runningFitness = 0, index = 0;
	int r = rand() % totFitness;
	
	//find the index of the chromosome to crossover
	while (r >= runningFitness)
	{
		runningFitness += population[index].GetFitness();
		index++;
	}
	index--; //index will always be one higher than the correct Chromosome
	return population[index];
}
