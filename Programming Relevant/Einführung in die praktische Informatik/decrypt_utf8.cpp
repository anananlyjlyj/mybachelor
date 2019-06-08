#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <locale>
#include <codecvt>
#include <algorithm>

std::wstring read_file(std::string filename)
{
    // Datei zum Lesen von wchar_t oeffnen
    std::wifstream infile(filename);

    // Daten einlesen
    std::wstringstream textstream;
    textstream << infile.rdbuf();

    // Inhalt als std::wstring zurueckgeben
    return textstream.str();
}

void write_file(std::string filename, std::wstring const & text)
{
    // Datei zum Schreiben von wchar_t oeffnen
    std::wofstream outfile(filename);

    // Text in Datei schreiben
    outfile << text;
}

struct Character
{
    wchar_t encrypted;
    wchar_t clear;
    int count;
};

//a)
int biggest_code(std::wstring const & text)
{
    int code = text[0];
    for(int i = 1; i < text.size(); i++)
    {
        int a = text[i - 1], b = text[i];
        if(a < b)
        {
            code = b;
        }
    }
    return code;
};



int main()
{
#if defined(_MSC_VER)
    // unter Windows/Visual Studio: locale fuer Deutsch definieren
    std::locale german("de-de");
#elif defined(__APPLE__)
    // unter MacOS: locale fuer Deutsch mit UTF-8 definieren
    std::locale german("de_DE.UTF-8");
#elif defined(__linux__)
    // unter Linux: locale fuer sprachunabhaengiges UTF-8 definieren
    std::locale german("C.UTF-8");
#else
    // sonst: verwende die Spracheinstellungen des Betriebssystems
    std::locale german("");
#endif

    // Konverter zwischen UTF-8 (Zeichentyp in der Datei) und
    // wchar_t (Zeichentyp im Programm) erzeugen
    std::locale codec(german, new std::codecvt_utf8<wchar_t>);

    // Konverter global setzen (er wird ab jetzt von allen
    // Ein-/Ausgabeoperationen in diesem Programm verwendet)
    std::locale::global(codec);

    // Datei einlesen
    std::wstring text = read_file("verschluesselt_utf8.txt");

    // Ihre Loesung hier
    
    //a) Fortsetzung
    int x = biggest_code(text);
    std::cout << "biggest code: " << x << '\n';
    
    //b)
    std::vector<Character> characters(x);
    for(int j = 0; j < x; j++)
    {
        characters[j].count = 0;
    }
    
    //c)
    for(int k = 0; k < text.size(); k++)
    {
        int y = std::tolower(text[k], german);
        if(characters[y].count == 0)
        {
            characters[y].encrypted = std::tolower(text[k], german);
        }
        characters[y].count += 1;
    }
    
    //d)
    std::sort(characters.begin(), characters.end(), 
        [](Character c, Character a)
        {
            return c.count < a.count;
        });
    
    //e)
    std::wstring alpha = read_file("buchstaben haeufigkeit utf8.txt");
    for(int l = 0; l < characters.size(); l++)
    {
        if(std::islower(characters[l].encrypted,german) && characters[l].count != 0)
        {
            characters[l].clear = alpha[l];
        }
    }
    
    //f)
    std::sort(characters.begin(), characters.end(), 
        [](Character c, Character a)
        {
            return c.encrypted < a.encrypted;
        });
        
    //g)
    for(int m = 0; m < text.size(); m++)
    {
        wchar_t z = std::tolower(text[m],german);
        for(int e = 0; e < characters.size(); e++)
        {
            if(characters[e].encrypted == z)
            {
                if(z != text[m])
                {
                    text[m] = std::toupper(characters[e].clear);
                }
                else
                {
                    text[m] = characters[e].clear;
                }
            }
        }
        
    }
    
    // Ergebnis in Datei schreiben
    write_file("entschluesselt.txt", text);
    
}


