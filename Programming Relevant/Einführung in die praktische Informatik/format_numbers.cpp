#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <cctype>
#include "format_numbers.hpp"

std::vector<int> vec_to_int(std::vector<double> v)
{
	std::vector<int> intv(v.size());
	std::transform(v.begin(), v.end(), intv.begin(), 
					[](double x)
					{
						int y = x / 1;
						return (x - y < 0.5)? y : y + 1;
					});
	return intv;
}

std::vector<double> vec_rounded(std::vector<double> v)
{
	std::vector<double> intv(v.size());
	std::transform(v.begin(), v.end(), intv.begin(), 
					[](double x)
					{
						int y = x * 100 / 1;
						double z = y / 100.0;
						return ( x - z < 0.005)? z : z + 0.01;
					});
	return intv;
}

std::string double_to_string(double x)
{
	int y = x * 100 / 1;
	double z = y / 100.0;
	double t = ( x - z < 0.005)? z : z + 0.01;		// auf zwei Nachkmmastellen gerundet werden
	std::string n = std::to_string(t);				// in einen String umwandeln
	int dot = n.find('.');
	if(dot == std::string::npos)
		n += ".00";
	else if(dot == n.size() - 2)
		n += '0';									// genau zwei Nachkommastellen sichern
	int strich = n.find('.') - 4;
	if(strich >= 0)
	{
		for(int i = strich; i >= 0; i -= 3)
		{
			n.insert(i + 1, '`');
		}
	}												// Apostroph einfuegen
	while(n.size() < 16)
		n.insert(0, ' ');							// Leerzeichen hinzufuegen
	return n;
}

std::vector<std::string> format_numbers(std::vector<double> v)
{
	std::vector<std::string> s;
	std::transform(v.begin, v.end(), s.begin(), double_to_string);
	return s;
}


int main()
{
	std::vector<std::string> s = format_numbers(numbers);
	for(int i = 0; i < s.size(); i++)
		std::cout<<s[i]<<' ';
	return 0;
	
}