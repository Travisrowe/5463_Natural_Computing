//Generate Circle : Travis Rowe : 10/17/18

#include <vector>
#include <string>
#include <iostream>
#include <cmath>

#define PI 3.14159265358979323846
static int N;

struct Point
{
	std::vector<double> distances;
	std::vector<double> coordinates; //x and y coordinates of this Point

	Point()
	{
		distances.resize(N);
		distances.assign(N, -1.0);
		coordinates.resize(2);
		coordinates[0] = coordinates[1] = 0;
	}
};

int main()
{
	//int N;
	double R;
	char TYPE;
	std::cin >> TYPE >> N >> R; //type is directed or undirected. N is number of vertices, R is radius
	std::cout << TYPE << " " << N << '\n';
	std::vector<Point> Circle(N); // does this call a constructor? maybe have default constructor set to (R, 0)
	double theta = 360 / N; //angle between any two Nodes on the circle
	double a, o, f, d, xPrime, yPrime; // x is R - adj. d is distance between the Nodes (d^2 = x^2 + opp^2)
	Circle[0].coordinates = { R, 0 };

	for (int i = 0; i < N; i++) //set coordinates and adjacent distances for all Points
	{
		//calculate next nodes coordinates
		double x = Circle[i].coordinates[0];
		double y = Circle[i].coordinates[1];
		xPrime = x * cos(theta * PI / 180.0) - y * sin(theta * PI / 180.0);
		yPrime = x * sin(theta * PI / 180.0) + y * cos(theta * PI / 180.0);
		Circle[(i + 1) % N].coordinates = { xPrime , yPrime };
	}

	//Calculate all non-adjacent distances between points
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (Circle[i].distances[j] == -1)
			{ //distance needs to be calculated
				double sum = 0;
				for (int dim = 0; dim < 2; dim++)
					sum += (Circle[i].coordinates[dim] - Circle[j].coordinates[dim]) * (Circle[i].coordinates[dim] - Circle[j].coordinates[dim]);
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
			//printf("%d %d %6f \n", i, j, Circle[i].distances[j]);
			std::cout << i << ' ' << j << ' ' << Circle[i].distances[j] << '\n';
		}
	}
}