// GeneticAlgorithmWithBits.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Population.h"

using namespace std;

const int POP_SIZE = 50;

int main()
{
	srand(2);
	Population a;
	int gen = 2;
	while (gen < 100)
	{
		//Create an empty population
		Population b(gen);
		a.EvolveGeneration(b);
		cout << "Generation " << gen << ": " << b.GetAverageFitness() << endl;
		gen++;
	}

	/*Chromosome x, y;
	x.Print();
	y.Print();
	cout << x.GetFitness() << endl;

	x.Crossover(y);
	x.Print();
	y.Print();
	x.Mutate();
	y.Mutate();*/
}
