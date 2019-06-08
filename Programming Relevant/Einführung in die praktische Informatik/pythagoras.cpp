#include <iostream>
#include <cmath>

bool is_square(int n)
{
	if(n % 4 == 2 || n % 4 == 3)
	{
		return false;
	}
	double y = std::sqrt(n);
	double z = std::floor(y);
	return (z * z == n)? true : false;
}

/*
Beweis:
(n^2) mod 4 = ((n mod 4)^2) mod 4
Fall 1:
	n mod 4 = 0;	=>	(n mod 4)^2 = 0;	=>	0 mod 4 = 0;	=>	(n^2) mod 4 = 0;
Fall 2:
	n mod 4 = 1;	=> 	(n mod 4)^2 = 1;	=>	1 mod 4 = 1;	=>	(n^2) mod 4 = 1;
Fall 3:
	n mod 4 = 2;	=>	(n mod 4)^2 = 4;	=>	4 mod 4 = 0;	=>	(n^2) mod 4 = 0;
Fall 2:
	n mod 4 = 3;	=> 	(n mod 4)^2 = 9;	=>	9 mod 4 = 1;	=>	(n^2) mod 4 = 1;

=>	(n^2) mod 4 = 0 oder 1;
*/

//c)
void pythagorean_triple(int bmax)
{
	for(int i = 1; i <= bmax; i++)
	{
		for(int j = 1; j < i; j++)
		{
			int k = i * i + j * j;
			if(is_square(k))
			{
				std::cout<<j<<"	"<<i<<"	"<<std::sqrt(k)<<std::endl;
			}
		}
	}
}

int main()
{
	std::cout<<"a"<<"	"<<"b"<<"	"<<"c"<<std::endl;
	pythagorean_triple(400);
	return 0;
}