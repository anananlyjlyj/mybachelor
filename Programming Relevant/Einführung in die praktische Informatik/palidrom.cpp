#include<cstring>
#include<cctype>
#include<iostream>
#include<cassert>

std::string to_lower(std::string s)
{
	for(int i = 0; i < s.size(); i++)
	{
		s[i] = std::tolower(s[i]);
	}
	return s;
		
}

std::string letters_only(std::string s)
{
	std::string t;
	for(int i = 0; i < s.size(); i++)
	{
		if(std::isalpha(s[i]))
		{
			t = t+ s[i];
		}
		
	}
	return t;
}

bool is_palindrom(std::string s)
{
	std::string ss = to_lower(s);
	std::string t = letters_only(ss);
	for(int i = 0; i < t.size() / 2; i++)
	{
		int r = t.size() - 1 - i;
		if(t[i] != t[r])
		{
			return false;
		}
	}
	return true;
}

int main()
{
	assert(is_palindrom("Rentner"));
	assert(is_palindrom("Lager0regal"));
	assert(is_palindrom("Ein Neg0er mit Ga1zelle zag2t im Re4gen nie"));
	assert(is_palindrom("Lagernotregal"));
	assert(is_palindrom("Ein Neg0er mit Ga1zelle zag2t nie im Re4gen"));
	std::cout << "Gib ein Wort oder einen Satz ein:\n";
	std::string s;
	std::getline(std::cin, s);
	std::string x = is_palindrom(s)? "ein" : "kein";
	std::cout << "Es ist "<<x<<" Palindrom.";
	return 0;
}
