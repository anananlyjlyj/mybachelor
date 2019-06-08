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

int biggest_code(std::wstring const & text)
{
    int res = 0;
    for(int k=0; k<text.size(); ++k)
    {
        if(res < text[k])
            res = text[k];
    }
    return res;
}

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

    // suche den groessten Zeichencode im Text
    int max = biggest_code(text);

    // erzeuge ein genuegend grosses Array
    std::vector<Character> characters(max+1);

    // Initialisiere das Array
    for(int k=0; k<characters.size(); ++k)
    {
        characters[k].count = 0;
        characters[k].clear = k;
        characters[k].encrypted = k;
    }

    // zaehle die Zeichen ohne Beachtung von Gross-/Kleinschreibung
    for(int k=0; k<text.size(); ++k)
    {
        characters[std::tolower(text[k], german)].count += 1;
    }

    // sortiere aufsteigend nach Haeufigkeit
    std::sort(characters.begin(), characters.end(),
              [](Character const & l, Character const & r)
              {
                  return l.count < r.count;
              });

    // Kleinbuchstaben nach aufsteigender Haeufigkeit einlesen
    std::wstring sorted_letters = read_file("buchstaben_haeufigkeit_utf8.txt");

    // ordne die Klarbuchstaben den Kleinbuchstaben nach Haeufigkeit zu
    // (nur wenn Zeichen tatsaechlich vorkam, also wenn count > 0).
    int j = 0;
    for(int k=0; k<characters.size(); ++k)
    {
        if(std::islower(characters[k].encrypted, german) && characters[k].count > 0)
        {
            characters[k].clear = sorted_letters[j];
            // std::wcout << "entschluesselt: " << characters[k].encrypted << " => " << characters[k].clear << std::endl;
            ++j;
        }
    }

    // characters wieder in die urspruengliche Reihenfolge bringen
    // (Index entspricht danach wieder characters[k].encrypted)
    std::sort(characters.begin(), characters.end(),
              [](Character const & l, Character const & r)
              {
                  return l.encrypted < r.encrypted;
              });

    // Zeichen entschluesseln (fuer Grossbuchstaben schauen wir beim
    // korrespondierenden Kleinbuchstaben nach und wandeln den
    // dort gefundenen Klarbuchstaben in Grossschreibung um)
    for(int k=0; k<text.size(); ++k)
    {
        wchar_t z = text[k];
        if(std::isupper(z, german))
        {
            text[k] = std::toupper(characters[std::tolower(z, german)].clear, german);
        }
        else
        {
            text[k] = characters[z].clear;
        }
    }

    // Ergebnis in Datei schreiben
    write_file("entschluesselt.txt", text);
}


