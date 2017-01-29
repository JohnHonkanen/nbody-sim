#include <glm\glm.hpp>
#include <iostream>
#include <string>
#include <float.h>

using namespace std;
using namespace glm;
int main()
{
	vec3 v(1, 2, 3);
	vec3 u(3, 2, 1);
	string str = "t";
	cout << (u + v).x << endl;
	cout << (u + v).y << endl;
	cout << (u + v).z << endl;

	mat2x2 m(1, 0, 2, 3);
	mat2x2 n(1, 1, 0, 2);

	mat2x2 mn = m*n;
	for (int i = 0; i<2; i++)
		for (int j = 0; j<1; j++)
			cout << mn[i][j] << "\t" << mn[i][j + 1] << endl;

	cin >> str;
}
