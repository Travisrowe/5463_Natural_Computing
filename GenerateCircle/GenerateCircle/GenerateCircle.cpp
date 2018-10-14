#include <vector>
#include <string>
#include <iostream>
#include <cmath>

#define PI 3.14159265358979323846

struct Point
{
	std::vector<double> distances;
	std::vector<double> coordinates; //x and y coordinates of this Point

	void Construct(int N) 
	{ 
		distances.resize(N); 
		distances.assign(N, -1.0);
		coordinates.resize(2); 
		coordinates[0] = coordinates[1] = 0; 
	}
};

int main()
{
	int N;
	double R;
	char TYPE;
	std::cin >> TYPE >> N >> R; //type is directed or undirected. N is number of vertices, R is radius
	std::vector<Point> Circle(N); // does this call a constructor? maybe have default constructor set to (R, 0)
	double theta = 360 / N; //angle between any two Nodes on the circle
	double a, o, x, d; // x is R - adj. d is distance between the Nodes (d^2 = x^2 + opp^2)
	for (int i = 0; i < N; i++) //set coordinates and adjacent distances for all Points
	{
		Circle[i].Construct(N);

		a = R * cos(theta * PI / 180.0);
		o = R * sin(theta * PI / 180.0);
		x = R - a;
		d = sqrt(x * x + o * o);
		Circle[i].distances[(i + 1) % N] = /*Circle[i].distances[(i - 1) % N] = */d;
		//if (Circle[i + 1 % N].coordinates[0] == 0 && Circle[i + 1 % N].coordinates[1] == 0) //(0, 0)
		Circle[(i + 1) % N].coordinates = { a , o };
	}

	//Calculate all non-adjacent distances between points
	for (int i = 0; i < N; i++)
	{
		for (int j = i + 1; j < N; j++)
		{
			if (Circle[i].distances[j] == -1)
			{ //distance needs to be calculated
				double sum = 0;
				for (int dim = 0; dim < 2; dim++)
					sum += Circle[i].coordinates[dim] - Circle[j].coordinates[dim] * Circle[i].coordinates[dim] - Circle[j].coordinates[dim];
				double dist = sqrt(sum);
				Circle[j].distances[i] = Circle[i].distances[j] = dist;
			}
		}
	}

	//print points
	for (int i = 0; i < N; i++)
	{
		for (int j = i + 1; j < N; j++)
		{
			printf("%d %d %6f \n", i, j, Circle[i].distances[j]);
		}
	}
}