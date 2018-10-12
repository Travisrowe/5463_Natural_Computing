#pragma once

using namespace std;

class Particle
{
private:
	const int NUM_DIMENSIONS = 2;
	const double C1 = 1.5;
	const double C2 = 1.5;
	const double C3 = 1;
	const double MAX_VEL = 1;
	//const vector<double> C = { 1.5, 1.5, 1 }; //weights by which velocity shifts

	double fitness;
	vector<double> pos;
	vector<double> vel;
	vector<double> pBest;
	double pBestFitness;

	double PickANum(double, double);
	void checkGBest();
	void checkPBest();
	void SetFitness();
public:
	//static so all Particles can access it and there's only one instance
	static vector<double> gBest;
	static double gBestFitness;

	Particle();
	~Particle();
	double GetFitness();
	double GetPBestFitness();
	double GetGBestFitness();
	vector<double> GetGBest();
	vector<double> GetPBest();
	void AlterVelocity();
	void Move();
	void PrintParticle();
	void PrintGBest();
	void SetRNGSeed();
};

