#include <algorithm>
#include <iostream>
#include <string>
#include <ctime>
#include <vector>

#include "text.hpp"


std::vector<std::string> split_words(std::string sentence)
{
    std::vector<std::string> words;
    
    while(sentence.size() > 0)
    {
        size_t first_char = sentence.find_first_not_of(' ');
        if(first_char == std::string::npos)
        {
            break;
        }
        
        size_t next_space = sentence.find(' ', first_char);
        words.push_back(sentence.substr(first_char, next_space));

        size_t next_char = sentence.find_first_not_of(' ', next_space);
        if(next_char == std::string::npos)
        {
            break;
        }
        sentence = sentence.substr(next_char);
    }
    return words;
}


std::string mix(std::string word)
{
    size_t first_letter = word.find_first_not_of("!.?,;:");
    size_t last_letter = word.find_last_not_of("!.?,;:");
    
    if(last_letter - first_letter <= 2) // nothing to shuffle
    {
        return word;
    }
    
    std::random_shuffle(word.begin() + first_letter + 1,
                        word.begin() + last_letter);
    
    return word;
}


std::string split_and_mix(std::string sentence)
{
    std::vector<std::string> words = split_words(sentence);
    if(words.size() == 0)
    {
        return "";
    }
    
    std::string shuffled = mix(words.front());
    for(size_t i = 1; i < words.size(); ++i)
    {
        shuffled += ' ' + mix(words[i]);
    }
    
    return shuffled;
}


void print_solution(std::string sample)
{
    std::cout << sample << std::endl << std::endl;
    std::cout << split_and_mix(sample) << std::endl << std::endl << std::endl;
}


int main()
{
    std::srand(time(0));
    
    print_solution(str1);
    print_solution(str2);
    print_solution(str3);
    print_solution(str4);
    print_solution(str5);
    
    return 0;
}