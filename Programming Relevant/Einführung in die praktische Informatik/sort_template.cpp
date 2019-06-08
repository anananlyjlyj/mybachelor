#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>
#include <algorithm> 

template <typename ElementType, typename LessThanFunctor>
bool check_sorted(std::vector<ElementType> const & v, LessThanFunctor less_than)
{
    for(int i = 1; i < v.size(); i++)
    {
        if(less_than(v[i], v[i - 1]))
            return false;
    } 
    return true;
}

template <typename Iterator, typename LessThanFunctor>
bool check_sorted(Iterator begin, Iterator end, LessThanFunctor less_than)
{
    Iterator iter = begin;
    while(iter != end)
    {
        ++iter;
        if(less_than(*iter, *begin))
            return false;
        ++begin;
    }
    return true;
}


template <typename ElementType, typename LessThanFunctor>
void insertion_sort(std::vector<ElementType> & v, LessThanFunctor less_than)
{
    for(int i = 1; i < v.size(); i++)
    {
        ElementType current = v[i];
        int j = i; // Anfangsposition der Luecke
        while(j > 0)
        {
            if(less_than(current, v[j - 1]))
            {
                v[j] = v[j - 1]; // Luecke eine Position nach links
            }
            else
            {
                break; // Luecke jetzt an richtiger Position
            }
            --j;
            v[j] = current; // Element in die Luecke einfuegen  
        }
    }
}

template <typename Iterator, typename LessThanFunctor>
void insertion_sort(Iterator begin, Iterator end, LessThanFunctor less_than)
{
    Iterator it = begin + 1;
    while(it != end + 1)
    {
        auto current = *it; 
        Iterator iter = it;   // Anfangsposition der Lueck 
        while(iter != begin)
        {
            
            if(less_than(current, *(iter - 1)))
            {
                *iter = *begin; // Luecke eine Position nach links
            }
            else
            {
                break; // Luecke jetzt an richtiger Position
            }
            --iter;
            *iter = current; // Element in die Luecke einfuegen  
            
        }
    ++it;
    }
        
}

int main()
{
    std::vector<double> v = {1.2, 2.1, 4.3, 3.4, 6.5, 5.6};
    assert(check_sorted(v, std::sort()));
    assert(!check_sorted(v, std::random_shuffle()));
    assert(!check_sorted(v, [](double a, double b){return a > b;}));
    
    assert(check_sorted(v.begin(), v.end(), std::sort()));
    assert(!check_sorted(v.begin(), v.end(), std::random_shuffle()));
    assert(!check_sorted(v.begin(), v.end(), std::random_shuffle()));
    
    assert(check_sorted(v, insertion_sort(v, [](double a, double b){return a < b;})));
    
    assert(check_sorted(v.begin(), v.end(), insertion_sort(v, [](double a, double b){return a < b;})));
    
    return 0;
}