#include <iostream>
#include <cassert>
#include <cmath>

double cbrt(double y)
{
	double z = (y > 0)? y : -y;
	double x = z / 3;
	while((x* x * x - z) > z * 1e-15 || (z - x* x * x) > z * 1e-15)
	{
		x = (x * 2.0 + (z / (x * x))) / 3.0;
	}
	return (y > 0)? x : -x;
}

int main()
{
	double x = std::pow(2.2, 1.0/3.0) - cbrt(2.2);
	assert(x <= 1e-10 || -x <= 1e-10);
	assert(cbrt(-2.2) == -cbrt(2.2));
	x = std::pow(3.3, 1.0/3.0) - cbrt(3.3);
	assert(x <= 1e-10 || -x <= 1e-10);
	assert(cbrt(-3.3) == -cbrt(3.3));
	x = std::pow(4.4, 1.0/3.0) - cbrt(4.4);
	assert(cbrt(-4.4) == -cbrt(4.4));
	assert(x <= 1e-10 || -x <= 1e-10);
	x = std::pow(5.5, 1.0/3.0) - cbrt(5.5);
	assert(x <= 1e-10 || -x <= 1e-10);
	assert(cbrt(-5.5) == -cbrt(5.5));
	return 0;
}

