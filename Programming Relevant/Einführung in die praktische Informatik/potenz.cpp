#include<cassert>
#include<cmath>
double sq(double x)
{
	return x * x;
}
double power(double x, int n)
{
	return (n == 1)?	x
				   :	(n % 2 == 0)?	sq(power(x, n/2))
				   :	x * power(x, n - 1);
}
int main()
{
	assert(power(3,3) == std::pow(3,3));
	assert(power(3,4) == std::pow(3,4));
	assert(power(3.3,3) == std::pow(3.3,3));
	assert(power(3.3,4) == std::pow(3.3,4));
	assert(power(2,5) == std::pow(2,5));
	assert(power(2,6) == std::pow(2,6));
	assert(power(2.2,5) == std::pow(2.2,5));
	assert(power(2.2,6) == std::pow(2.2,6));
	return 0;
}
/*
Warum?
z.B.
x^8 = sq(power(x, 4)) = sq(sq(power(x, 2))) = sq(sq(sq(power(x,1))));
nur 2 Rekursionen und 3 Multiplikationen.
Wenn 2 rekursive Aufrufen von power() verwendet werden:
x^8 = power(x, 8) = power(power(x, 4), 2) = power(power(power(x, 2),2), 2) = power(power(power(power(x, 1), 2), 2), 2);
3 Rekursionen und 4 Multiplikationen.
Mit weniger Rekursionen und Multiplikationen laeuft das Programm schneller.
*/
