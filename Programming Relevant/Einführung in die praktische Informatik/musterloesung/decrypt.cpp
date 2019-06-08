#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <cctype>

std::string read_file(const std::string & path);
std::map<char, int> frequency(const std::string & text);
std::map<int, char> sorted_map(const std::map<char, int> & counts);
std::map<char, char> decrypt_map(const std::map<int, char> & sorted);
void decrypt_text(std::string & text, const std::map<char, char> & decrypt);

// a)
// 1.5 Punkte
std::string read_file(const std::string &path)
{
    // Datei oeffnen
    std::ifstream infile(path);
    // leerer String fuer den eingelesenen Text
    std::string text;
    // leerer String fuer die aktuelle Zeile
    std::string line;
    while (infile) // noch Daten im File?
    {
        // naechste Zeile einlesen ...
        std::getline(infile, line);
        text += line + "\n";
    }
    return text;
}

// b)
// 4 Punkte
std::map<char, int> frequency(const std::string & text)
{
    std::map<char, int> counts;
    for (char c = 'a'; c <= 'z'; ++c)
    {
        // alle Zeichen als Kleinbucgstaben in die Map setzen
        // und den Zaehler mit 0 initialisieren
        counts[c] = 0;
    }
    for (auto c = text.begin(); c != text.end(); ++c)
    {
        // zaehlen wie oft alle Zeichen vorkommen, dazu
        // Grossbuchstaben erst in Kleinbuchstaben wandeln
        if (std::isalpha(*c))
        {
            counts[std::tolower(*c)] += 1;
        }
    }
    return counts;
}

// c)
// 3 Punkte
std::map<int, char> sorted_map(const std::map<char, int> & counts)
{
    std::map<int, char> sorted;
    // die map 'sorted' fuellen, so dass die Schluessel und Werte aus 'counts'
    // (d.h. (*c).first und (*c).second) vertauscht werden
    // Achtung: Das funktioniert nur, wenn die counts eindeutig sind,
    //          was hier gluecklicherweise zutrifft.
    for (auto c = counts.begin(); c != counts.end(); ++c)
    {
        sorted[(*c).second] = (*c).first;
    }
    return sorted;
}

// 0.5 Punkte
const std::vector<char> letters = {'z', 'j',
               'q', 'x', 'k', 'v', 'b', 'y',
               'g', 'p', 'w', 'f', 'm', 'c',
               'u', 'l', 'd', 'r', 'h', 's',
               'n', 'i', 'o', 'a', 't', 'e'};

// d)
// 4 Punkte
// besonders auch Gross/Kleinschreibung beachten
// (kann auch in e passieren)
std::map<char, char> decrypt_map(const std::map<int, char> & sorted)
{
    std::map<char, char> decrypt;
    int i = 0;
    for (auto c = sorted.begin(); c != sorted.end(); ++c, ++i)
    {
        // Dekodierung Kleinbuchstabe
        decrypt[c->second] = letters[i];
        // Dekodierung korrespondierender Grossbuchstabe
        decrypt[std::toupper(c->second)] = std::toupper(letters[i]);
    }
    return decrypt;
}

// e)
// 3 Punkte,
// besonders das Erhalten der Zeichen, die keine Buchstaben sind
void decrypt_text(std::string & text,
                  const std::map<char, char> & decrypt)
{
    for (auto c = text.begin(); c != text.end(); ++c)
    {
        if (std::isalpha(*c)) // nur Buchstaben dekodieren
        {
            // Benutze 'decrypt.at(*c)', weil 'decrypt[*c]'
            // fuer eine read-only map undefiniert ist
            *c = decrypt.at(*c);
        }
    }
}

void write_file(const std::string & text, const std::string & file)
{
    std::ofstream outfile(file);
    outfile << text;
}

int main()
{
    std::string text = read_file("encrypted_text.txt");
    std::map<char, int> count = frequency(text);
    std::map<int, char> sorted = sorted_map(count);
    std::map<char, char> decrypt = decrypt_map(sorted);
    decrypt_text(text, decrypt);
    write_file(text, "decrypted_text.txt");

    return 0;
}
