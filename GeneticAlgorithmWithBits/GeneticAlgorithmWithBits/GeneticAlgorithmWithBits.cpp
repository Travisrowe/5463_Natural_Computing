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
	cout << "Generation 1: " << a.GetAverageFitness() << endl;
	int gen = 2;
	bool convergence = false;
	while (convergence == false && gen < 1000)
	{
		if (gen >= 900)
			int x = 0;
		//Create an empty population
		Population b(gen);
		a.EvolveGeneration(b);
		cout << "Generation " << gen << ": " << b.GetAverageFitness() << endl;
		a = b;
		gen++;
	}
	if (convergence)
	{
		cout << "Convergence!\n";
		cout << "Generation " << gen << ": " << a.GetAverageFitness() << endl;
	}
}
