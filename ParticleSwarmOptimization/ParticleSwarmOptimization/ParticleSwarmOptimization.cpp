// ParticleSwarmOptimization.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Particle.h"

#define MINIMA true

//initialize static variables
vector<double> Particle::gBest = { 0 };
#if MINIMA
double Particle::gBestFitness = DBL_MAX;
#else //MAXIMA
double Particle::gBestFitness = DBL_MIN;
#endif

int main()
{
	const int N_SIZE = 20; //neighborhood size
	vector<Particle> neighborhood(N_SIZE);

	//Set the seed for the static RNG.
	neighborhood[0].SetRNGSeed();

	const int NUM_ITERATIONS = 1000;
	for (int iter = 0; iter <= NUM_ITERATIONS; iter++)
	{
		for (int i = 0; i < N_SIZE; i++)
		{
			//Move particles, printing every 100 iterations
			/*if(iter % 100 == 0)
				neighborhood[i].PrintParticle();*/
			neighborhood[i].Move();
		}
		for (int i = 0; i < N_SIZE; i++)
		{
			//Alter Velocity of particles
			neighborhood[i].AlterVelocity();
		}
		if (iter % 100 == 0)
		{
			cout << "Iteration: " << iter << '\n';
			neighborhood[0].PrintGBest();
		}
	}
}