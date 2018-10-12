#include "pch.h"
#include "Particle.h"

//#define SEED 1
#define MINIMA true

default_random_engine & global_urng()
{
	static default_random_engine u{};
	return u;
}

//called by Move(). Adjusts the velocity of the Particle toward
//pBest and gBest by factors C2 and C3. C1 represents the factor
//by which the Particle continues moving in its original direction
void Particle::AlterVelocity()
{
	double rNum = PickANum(0, 1);
	for (int i = 0; i < NUM_DIMENSIONS; i++)
	{
		vel[i] = C1 * vel[i] +
			C2 * rNum * (pBest[i] - pos[i]) +
			C3 * rNum * (gBest[i] - pos[i]);
		
		if (vel[i] > MAX_VEL)
			vel[i] = MAX_VEL;
		else if (vel[i] < -1 * MAX_VEL)
			vel[i] = -1 * MAX_VEL;
	}
}

//called when any pBest is updated in checkPBest().
//checks for new global best
void Particle::checkGBest()
{
#if MINIMA
	if (pBestFitness < gBestFitness)
#else //MAXIMA
	if(pBestFitness > gBestFitness)
#endif
	{
		gBest = pBest;
		gBestFitness = pBestFitness;
	}
}

//Called after SetFitness(). Checks for new pBest.
void Particle::checkPBest()
{
#if MINIMA
	if (fitness < pBestFitness)
#else
	if (fitness > pBestFitness)
#endif
	{
		pBest = pos;
		pBestFitness = fitness;

		checkGBest();
	}
}

double Particle::GetFitness()
{
	return fitness;
}

vector<double> Particle::GetGBest()
{
	return gBest;
}

vector<double> Particle::GetPBest()
{
	return pBest;
}

double Particle::GetGBestFitness()
{
	return gBestFitness;
}

double Particle::GetPBestFitness()
{
	return pBestFitness;
}

void Particle::Move()
{
	for (int i = 0; i < NUM_DIMENSIONS; i++)
	{
		//if pos goes out of bounds ( -500, 500 ) wrap pos around to other side
		//so if vel is positive, pos will go from 500 to -500
		//if vel is negative, pos will go from -500 to 500

		if(!(pos[i] + vel[i] > 500 || pos[i] + vel[i] < -500))
			pos[i] += vel[i];
		else if (pos[i] + vel[i] > 500) //velocity is positive
		{
			pos[i] = -500 + (pos[i] + vel[i] - 500);
		}
		else //velocity is negative
		{
			pos[i] = 500 - (pos[i] + vel[i] + 500);
		}
	}
	SetFitness();
}

Particle::Particle()
{
	pos.resize(NUM_DIMENSIONS);
	vel.resize(NUM_DIMENSIONS);
	for (int i = 0; i < NUM_DIMENSIONS; i++)
	{
		pos[i] = PickANum(-500, 500);
		vel[i] = PickANum(-1, 1);
	}

//Set pBest to an arbitrary MAX or MIN value
//so that it will be set by CheckPBest
#if MINIMA
	pBestFitness = DBL_MAX;
#else //MAXIMA
	pBestFitness = DBL_MIN;
#endif
	SetFitness();
}

Particle::~Particle()
{
	pos.clear();
	vel.clear();
}

//returns a random double between from and to
double Particle::PickANum(double from, double to)
{
	static uniform_real_distribution<> d{};
	using param_t = decltype(d)::param_type;
	return d(global_urng(), param_t{ from, to });
}

void Particle::PrintGBest()
{
		cout << "GBest: (";
		for (int i = 0; i < NUM_DIMENSIONS; i++)
		{
			cout << gBest[i];
			if (i != NUM_DIMENSIONS - 1)
				cout << ", ";
			else
				cout << ")\n";
		}
		cout << "GBest Fitness: " << gBestFitness << "\n\n";
}

void Particle::PrintParticle()
{
	cout << "Position: (";
	for (int i = 0; i < NUM_DIMENSIONS; i++)
	{
		cout << pos[i];
		if (i != NUM_DIMENSIONS - 1)
			cout << ", ";
		else
			cout << ")\n";
	}
	cout << "Velocity: (";
	for (int i = 0; i < NUM_DIMENSIONS; i++)
	{
		cout << vel[i];
		if (i != NUM_DIMENSIONS - 1)
			cout << ", ";
		else
			cout << ")\n";
	}
	cout << "Current Fitness: " << fitness << '\n';
	cout << "Personal Best Position: (";
	for (int i = 0; i < NUM_DIMENSIONS; i++)
	{
		cout << pBest[i];
		if (i != NUM_DIMENSIONS - 1)
			cout << ", ";
		else
			cout << ")\n";
	}
	cout << "Personal Best Fitness: " << pBestFitness << "\n\n";
}

void Particle::SetFitness()
{
	//Schweffel function
	double sum = 0;
	for (int i = 0; i < NUM_DIMENSIONS; i++)
	{
		sum += pos[i] * sin(sqrt(abs(pos[i])));
	}
	fitness = 418.9829 * NUM_DIMENSIONS - sum;
	checkPBest();
}

void Particle::SetRNGSeed()
{
#ifdef SEED //use defined seed
	global_urng().seed(SEED);
#else //generate a random seed
	static random_device rd{};
	global_urng().seed( rd() );
#endif // SEED
	//cout << "Current seed = " << global_urng().seed() << '\n';
}