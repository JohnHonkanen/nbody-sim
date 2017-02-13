
#include "Rnd.h"

float rnd(int rangemin, int rangemax)			// random float within supplied range...
{
	return rand() % (rangemax - rangemin) + rangemin;
}


