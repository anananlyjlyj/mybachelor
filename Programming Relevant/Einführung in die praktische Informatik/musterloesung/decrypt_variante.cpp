#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <cctype>

int main()
{
    //a) Lesen Sie die Datei ein
    std::ifstream infile("encrypted_text.txt"); // Datei oeffnen
    std::string text;   // leerer String für den eingelesenen Text
    std::string line;   // leerer String für die aktuelle Zeile
    while(infile) // noch Daten im File?
    {
        std::getline(infile, line); // naechste Zeile einlesen ...
        text += line + "\n";        // ... und an den Text anhaengen
    }

    //b)+c) Sortierung bei einem normalen britisch-englischen Text
    std::vector<char> letters = { 'z', 'j', 'q', 'x', 'k', 'v', 'b', 'y', 'g', 'p', 'w', 'f', 'm', 'c', 'u', 'l', 'd', 'r', 'h', 's', 'n', 'i', 'o', 'a', 't', 'e' };

    //b) map fuer das Zaehlen der Buchstaben erzeugen
    //   und mit 0 initialisieren
    std::map<char, int> count;
    for(int k=0; k<letters.size(); ++k)
    {
        count[letters[k]] = 0;
    }

    //b) Bestimmen der Buchstabenhaeufigkeit
    //   Grossbuchstaben werden dabei in Kleinbuchstaben konvertiert
    for(int k=0; k<text.size(); ++k)
    {
        if(std::isalpha(text[k]))
        {
            ++count[std::tolower(text[k])];
        }
    }

    //c) Sortieren nach aufsteigender Haeufigkeit:
    //   Erzeugen einer neuen map, wo Schluesel und Werte
    //   (d.h. (*i).first und (*i).second) vertauscht sind
    //   Achtung: Das funktioniert nur, wenn die Haeufigkeiten
    //            eindeutig sind, was hier gluecklicherweise
    //            zutrifft.
    std::map<int, char> sorted;
    for(auto i=count.begin(); i!=count.end(); ++i)
    {
        sorted[(*i).second] = (*i).first;
    }

    //d) Zuordnung von Klarbuchstaben zu verschluesselten Buchstaben
    std::map<char, char> decrypt;
    int k=0;
    for(auto i=sorted.begin(); i!=sorted.end(); ++i, ++k)
    {
        // entschluesselter Kleinbuchstabe
        decrypt[(*i).second] = letters[k];
        // entschluesselter korrespondierender Grossbuchstabe
        decrypt[std::toupper((*i).second)] = std::toupper(letters[k]);
    }

    //e) Text in-place entschluesseln
    for(int k=0; k<text.size(); ++k)
    {
        // nur Buchstaben entschluesseln, andere Zeichen bleiben erhalten
        if(std::isalpha(text[k]))
        {
            text[k] = decrypt[text[k]];
        }
    }
    // text enthaelt jetzt den entschluesselten Text

    std::ofstream outfile("decrypted_text.txt");    // Datei oeffnen
    outfile << text;                                // text in die Datei schreiben
}


