// GeneticAlgorithmWithBits.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Population.h"
//#include<time.h>>
using namespace std;

const int POP_SIZE = 50;

int main()
{
	srand(time(NULL));
	int totFitness = 0, totGen = 0, totConverged = 0;
	for (int i = 0; i < 100; i++)
	{
		Population a;
		//cout << "Generation 1: " << a.GetAverageFitness() << endl;
		int gen = 2;
		bool convergence = false;
		while (convergence == false && gen < 1000)
		{
			//Create an empty population
			Population b(gen);
			a.EvolveGeneration(b);
			//int avgFit = b.GetAverageFitness();
			//cout << "Generation " << gen << ": " << avgFit << endl;
			/*if (avgFit == 35)
				int x = 0;*/
			a = b;
			convergence = a.CheckConvergence();
			gen++;
			if (gen == 999)
				cout << "Max generation limit reached. Average fitness of this generation: "
				<< a.GetAverageFitness() << endl;
		}
		if (convergence)
		{
			int avgFit = a.GetAverageFitness();
			cout << "Convergence!\n";
			cout << "Generation: " << gen << ". Average fitness of generation: " << avgFit << endl;
			totFitness += avgFit;
			totGen += gen;
			totConverged++;
		}
	}
	cout << "Total programs that reached convergence: " << totConverged << endl;
	if (totConverged != 0)
	{
		cout << "Average fitness of converged generations: " << totFitness / totConverged << endl;
		cout << "Average generation of convergence: " << totGen / totConverged << endl;
	}
}
