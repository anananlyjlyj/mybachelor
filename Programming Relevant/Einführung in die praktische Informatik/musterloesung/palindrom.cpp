//Musterloesung 4.3 Plaindrome

#include <iostream>
#include <string>
#include <cctype>
#include <assert.h>

std::string to_lower(std::string s);            // a)
std::string letters_only(std::string s);        // b)
bool is_palindrom(std::string s);               // c)

int main()
{
    //tests c)
    assert( is_palindrom("Lagerregal"));
    assert( is_palindrom("Nie grub Ramses Marburg ein."));
    assert(!is_palindrom("Test"));

    std::string poem =     "";
    poem +=    "Dammit I知 mad.";
    poem +=    "Evil is a deed as I live.";
    poem +=    "God, am I reviled? I rise, my bed on a sun, I melt.";
    poem +=    "To be not one man emanating is sad. I piss.";
    poem +=    "Alas, it is so late. Who stops to help?";
    poem +=    "Man, it is hot. I知 in it. I tell.";
    poem +=    "I am not a devil. I level Mad Dog.";
    poem +=    "Ah, say burning is, as a deified gulp,";
    poem +=    "In my halo of a mired rum tin.";
    poem +=    "I erase many men. Oh, to be man, a sin.";
    poem +=    "Is evil in a clam? In a trap?";
    poem +=    "No. It is open. On it I was stuck.";
    poem +=    "Rats peed on hope. Elsewhere dips a web.";
    poem +=    "Be still if I fill its ebb.";
    poem +=    "Ew, a spider� eh?";
    poem +=    "We sleep. Oh no!";
    poem +=    "Deep, stark cuts saw it in one position.";
    poem +=    "Part animal, can I live? Sin is a name.";
    poem +=    "Both, one� my names are in it.";
    poem +=    "Murder? I知 a fool.";
    poem +=    "A hymn I plug, deified as a sign in ruby ash.";
    poem +=    "A Goddam level I lived at.";
    poem +=    "On mail let it in. I知 it.";
    poem +=    "Oh, sit in ample hot spots. Oh wet!";
    poem +=    "A loss it is alas (sip). I壇 assign it a name.";
    poem +=    "Name not one bottle minus an ode by me:";
    poem +=    "Sir, I deliver. I知 a dog";
    poem +=    "Evil is a deed as I live.";
    poem +=    "Dammit I知 mad.";

    assert( is_palindrom(poem));

    // input d)
    std::string s;
    while(s!= "0"){
        std::cout << "Gib ein Wort oder einen Satz ein (0 fuer Abbruch):\n";
        std::getline(std::cin, s);
        if(s !="0"){
            if (is_palindrom(s)){
                std::cout << s + " ist ein Palindrom" << std::endl;
            }
            else{
                std::cout << s + " ist kein Palindrom" << std::endl;
            }
        }
    }


    return 0;
}


// a) function which converts string to all lower case
// I did not do any error handling with Umlauts
// (my system locale does some strange things)
std::string to_lower(std::string s)
{
    std::string tmp_str = "";

    //iterate over all chars and turn to lower
    for(int i = 0; i < s.length(); i++)
    {
        // an explicit cast is not needed because tolower's 'int'
        // result is automaticaly converted to 'char'
        tmp_str += std::tolower(s[i]);
    }

    return tmp_str;
}

// b) function which removes all non alpha chars from a given string
std::string letters_only(std::string s)
{
    std::string tmp_str;

    for(int i = 0; i < s.length(); i++)
    {
        if (std::isalpha(s[i]))
        {
            tmp_str += s[i];
        }
    }

    return tmp_str;
}

// c) test if string is palindrome
bool is_palindrom(std::string s)
{
    // remove non-aplpha chars and convert to all lower case
    std::string tmp_str = to_lower(letters_only(s));

    // palindrom testing: iterate of the first half of the string
    // (using truncating div for strings of odd length)
    for(int i = 0; i < tmp_str.length()/2; i++)
    {
        // compare first to last char, second to second to last
        // and so on
        if(tmp_str[i] != tmp_str[tmp_str.length() -1 -i]){
            return false;   // abort if missmatch found
        }
    }

    return true; // if no missmatch was found, s is palindrome
}
