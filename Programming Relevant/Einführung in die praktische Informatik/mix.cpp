#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include "text.hpp"


std::vector<std::string> split_words(std::string s)
{
	std::vector<std::string> sw;
	while(1)
	{
	    while (s[0] == ' ')
	    {
	        s = s.substr(1);
	    }										//mehrere Leerzeichen weglassen
	    int p = s.find(' ');					//die erste Wort(Leerzeichen) finden
	    if(p == std::string::npos)
	        break;								//while(1) endet vor der letzte Wort
		sw.push_back(s.substr(0, p));
		s = s.substr(p + 1);
	}
    sw.push_back(s);
	return sw;
}

std::string mix(std::string s)
{
    int a = 0, e = s.size() - 1;
	while(!std::isalpha(s[a]))
	{
		a++;
	}											//erste Buchstabe finden
	while(!std::isalpha(s[e]))
	{
		e--;
	}											//letzte Buchstabe finden
    std::string mixs = s.substr(a + 1, e  - a - 1);
	random_shuffle(mixs.begin(), mixs.end());	
	for(int i = 0; i < e - a - 1; i++)
	{
	    s[a + 1 + i] = mixs [i];
	}																		
	return s;
}

std::string split_and_mix(std::string s)
{
	std::vector<std::string> sw = split_words(s);
	std::string ss = "";
	for(int i = 0; i <sw.size(); i++)
	{
		ss = ss + mix(sw[i]) + " ";
	}
	return ss;
}

int main()
{
	std::string s = "Blaukraut bleibt Blaukraut und Brautkleid bleibt Brautkleid.";
	std::cout << s<<"\n"<<split_and_mix(s)<<" \n";
	std::cout << str1<<"\n"<<split_and_mix(str1)<<" \n";
	std::cout << str2<<"\n"<<split_and_mix(str2)<<" \n";
	std::cout << str3<<"\n"<<split_and_mix(str3)<<" \n";
	std::cout << str4<<"\n"<<split_and_mix(str4)<<" \n";
	std::cout << str5<<"\n"<<split_and_mix(str5)<<" \n";
	return 0;
}