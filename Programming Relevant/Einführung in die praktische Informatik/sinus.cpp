#include<iostream>
#include<cmath>
double taylor_sin(double x)
{
	return x * (1 - x * x / 6.0);
}
double winkel(double x)
{
	return x * M_PI / 180;
}
double pump_sin(double sin_third)
{	
	return sin_third * (3 - 4 * sin_third * sin_third);
}
double intervall(double x)
{
	return (x  <= M_PI)? x : intervall(x - M_PI *２);
}
double my_sin(double x)
{
	x = intervall (x);
	double y = (x > 0)?	x : -x;
	double x0 = taylor_sin(x);
	return (y <= x0)? x0 : pump_sin(my_sin((x / 3.0)));
}
int main()
{
	int f[20] = {5, 10, 20, 45, 90 ,135, 180, 225, 270, 315, -5, -10, -20, -45, -90 ,-135, -180, -225, -270, -315};
	std::cout<<"x"<<"	std::sin(x)"<<"		taylor_sin(x)"<<"	Approximationsfehler"<<"		my_sin(x)"<<"	Approximationsfehler"<<std::endl;
	for (int i = 0; i <= 20; i++)
	{
		double x = winkel(f[i]);
		double s = std::sin(x);
		double y = taylor_sin(x);
		double z = my_sin(x);
		double f1 = (s - y > 0)? s - y : y - s;
		double f2 = (s - z > 0)? s - z : z - s;
		std::cout<<x<<"	"<<s<<"	"<<y<<"	"<<f1<<"	"<<z<<f2<<"	"<<std::endl;
	}
	return 0;
}