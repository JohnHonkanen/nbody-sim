#include "Rnd.h"

double rnd(double rangemin, double rangemax)			// random float within supplied range...
{
	double f = (double)rand() / RAND_MAX;
	return f * (rangemax - rangemin) + rangemin;
}

int irnd(int rangemin, int rangemax)			// random float within supplied range...
{
	int f = (int)rand() / RAND_MAX;
	return f * (rangemax - rangemin) + rangemin;
}



double exponent(double lambda) {
	return -log(1 - rnd(0,1)) / lambda;
}
