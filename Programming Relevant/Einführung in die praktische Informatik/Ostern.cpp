#include <string>
#include <cassert>
#include <string>
#include <sstream>

template<typename T>
std::string to_string(const T& value)
{
    std::ostringstream stream;
    stream << value;
    return stream.str();
}

std::string easter(int year)
{
	int y = year;
	int a = y % 19;
	int b = y % 4; 
	int c = y % 7;
	int k = y/100;
	int p = (8 * k + 13) / 25;
	int q = k / 4;
	int m = (15 + k - p - q) % 30;
	int d = (19 * a + m) % 30;
	int n = (4 + k - q) % 7;
	int e = (2 * b + 4 * c + 6 * d + n) % 7;
	int x =  22 + d + e; 
	int z = (x == 57)?	50
					: (x == 56 && d == 28 && a > 10)? 49 
					: x;
	return "Ostern ist am " + ((z < 32)? to_string(z) + ".Maerz" : to_string(z-31) + ".April");
}
int main()
{
	assert(easter(2121) == "Ostern ist am 6.April");
	assert(easter(2020) == "Ostern ist am 12.April");
	assert(easter(2000) == "Ostern ist am 23.April");
	assert(easter(1919) == "Ostern ist am 20.April");
	assert(easter(1818) == "Ostern ist am 22.Maerz");
	assert(easter(1800) == "Ostern ist am 13.April");
	assert(easter(1717) == "Ostern ist am 28.Maerz");
	assert(easter(1700) == "Ostern ist am 11.April");
	assert(easter(1616) == "Ostern ist am 3.April");
	assert(easter(1583) == "Ostern ist am 10.April");
	return 0;
}