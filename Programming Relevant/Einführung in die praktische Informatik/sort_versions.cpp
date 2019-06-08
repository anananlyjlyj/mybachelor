#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <algorithm> 
#include <cassert>
#include "sort_versions.hpp"


std::vector<int> split_version(std::string version)
{
	std::vector <int> number;
	while(version.find('.') != std::string::npos)
	{
		int x = std::atoi(version.c_str());
		number.push_back(x);
		int s = version.find('.');
		if(s == std::string::npos)
			break;
		version = version.substr(s + 1);
	}
	number.push_back(std::atoi(version.c_str()));
	return number;
}

bool version_less(std::string v1, std::string v2)
{
	std::vector <int> n1 = split_version(v1), n2 = split_version(v2);
	while(n1.size() > n2.size())
	{
		n2.push_back(0);
	}
	while(n1.size() < n2.size())
	{
		n1.push_back(0);
	}
	for(int i = 0; i < n1.size(); i++)
	{
		if(n1[i] < n2[i])
			return true;
		if(n1[i] > n2[i])
			break;
	}
	return false;
}

int main()
{
	std::vector <int> s = split_version("1.2.3.4.5");
	for(int i = 0; i < s.size(); i++)
	{
		std::cout<<s[i]<<std::endl;
	}
	
	assert(version_less("3.1.3","3.2.4"));
	assert(version_less("3.1","3.2.4"));
	assert(version_less("3.1.3","3.2"));
	assert(!version_less("3.2.6","3.2.4"));
	assert(!version_less("3.3","3.2.4"));
	assert(!version_less("3.1.3","3"));
	
	std::sort(versions.begin(),versions.end(),version_less);
	for(int i = 0; i < versions.size(); i++)
	{
		std::cout<<versions[i]<<std::endl;
	}
	
	return 0;
}