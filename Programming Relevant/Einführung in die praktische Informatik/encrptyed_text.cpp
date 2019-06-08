#include <iostream>
#include <fstream>
#include <map>
#include <cctype>
#include <vector>

void entschluesseln(std::string &s, std::map<char, char> decrypt)			// e)
{
	for(int i = 0; i < s.size(); i++)
	{
		if(std::isalpha(s[i]))
		{
			s[i] = decrypt[s[i]];
		}
			
	}
}



int main()
{
	std::ifstream infile("encrypted_text.txt"); // Datei oeffnen
	std::string text; // leerer String fuer den eingelesenen Text
	std::string line; // leerer String fuer die aktuelle Zeile
	while(infile)
	{
	std::getline(infile, line); // naechste Zeile einlesen ...
	text += line + "\n"; // ... und an den Text anhaengen
	}
	
	std::map<char, int> count;	// b)
	for(char c = 'a'; c <= 'z'; c++)
	{
		int mal = 0;
		for(int i = 0; i < text.size(); i++)
		{
			if(text[i] == c || text[i] == std::toupper(c))
				mal++;
		}
		count[c] = mal;
	}
	
	std::map<int,char> sorted;	// c)
	for(char c2 = 'a'; c2 <= 'z'; c2++)
	{
		sorted[count[c2]] = c2;
	}
	
	std::string s = "z j q x k v b y g p w f m c u l d r h s n i o a t e";
	std::vector<char> letters;
	for(int i = 0; i < s.size(); i+=2)
	{
		letters[i] = s[i];
	}
	
	std::map<char, char> decrypt;	// d)
	auto it = sorted.begin();
	for(int j = 0; j < letters.size(); j++, it++)
	{
		decrypt[it->second] = letters[j];
	}
		
	
	entschluesseln(text, decrypt);
	
	std::ofstream outfile("decrypted_text.txt"); // Datei oeffnen
	outfile << text; // text enthaelt jetzt den entschluesselten Text
	
	return 0;
}

