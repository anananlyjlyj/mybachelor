#include<iostream>
#include<cassert>
#include<algorithm>
#include<vector>

//a)
template<typename ElementType, typename LessThanFunctor>
bool check_sorted(std::vector<ElementType> const & v, LessThanFunctor less_than)
{
    for(int k = 1; k < v.size(); ++k)
    {
        if(less_than(v[k], v[k - 1]))
            return false;
    }
    return true;
}

//b)
template<typename Iterator, typename LessThanFunctor>
bool check_sorted(Iterator begin, Iterator end, LessThanFunctor less_than)
{
    if(begin == end)
        return true;
    Iterator next = begin;
    ++next;
    for(;next != end; ++begin, ++next)
    {
        if(less_than(*next, *begin))
            return false;
    }
    return true;
}

//c)
//pass-by-reference, weil v veraendert werden soll 
template<typename ElementType, typename LessThanFunctor>
bool insertion_sort(std::vector<ElementType> & v, LessThanFunctor less_than)
{
    for(int k = 1; k < v.size(); ++k)
    {
        ElementType current = v[k];
        int j = k;  // Anfangsposition der Luecke
        while(j > 0)
        {
            if(less_than(current, v[j -1]))
                v[j] = v[j - 1];    // Luecke eine Position nach links
            else 
                break;
            --j;
        }
        v[j] = current;
    }
}

//b)
template<typename Iterator, typename LessThanFunctor>
bool check_sorted(Iterator begin, Iterator end, LessThanFunctor less_than)
{
    if(begin == end)
        return;
    Iterator k = begin;
    ++k;
    for(;k != end; ++begin, ++k)
    {
        auto current = *k;
        Iterator j = k;
        Iterator j_1 = k;   // soll j - 1 darstellen, da *(j - 1) nicht erlaubt in dieser Aufgabe ist 
        --j_1;
        while(j != begin)
        {
            if(less_than(current, *(j_1)))
            {
                *j = *(j_1)
            }
            else 
                break;
            --j_1;
            --j;
        }
        *j = current;
    }
}

double std_sort_time(int n)
{
    std::vector<int> v(n);
    std::iota(v.begin(), v.end(), 0);
    std::random_shuffle(v.begin, v.end());
    
    auto start = std::chrono::high_resolution_clock::now();
    std::sort(v.begin(), v.end());
    auto stop = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double> diff = stop - start;
    return diff.count();
}

double insert_best(int n)
{
    std::vector<int> v(n);
    std::iota(v.begin(), v.end(), 0);
    
    auto start = std::chrono::high_resolution_clock::now();
    insertion_sort(v);
    auto stop = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double> diff = stop - start;
    return diff.count();
}

double insert_worst(int n)
{
    std::vector<int> v(n);
    std::iota(v.begin(), v.end(), 0);
    std::reverse(v.begin(),v.end());
    
    auto start = std::chrono::high_resolution_clock::now();
    insertion_sort(v);
    auto stop = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double> diff = stop - start;
    return diff.count();
}

double insert_avg(int n)
{
    std::vector<int> v(n);
    std::iota(v.begin(), v.end(), 0);
    std::random_shuffle(v.begin, v.end());
    
    auto start = std::chrono::high_resolution_clock::now();
    insertion_sort(v);
    auto stop = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double> diff = stop - start;
    return diff.count();
}

template<typename Measure>
double do_time(int n, int rounds, Measure m)
{
    double min = 100000;
    for(int i = 0; i < rounds; ++i)
    {
        double t = m(n);
        if(t < min)
        {
            min = t;
        }
    }
    return min;
}

template<typename Measure, typename Complexity>
void find_constant(int n, int rounds, Measure m, Complexity c)
{
    double time = do_time(n, rounds, m);
    double steps = c(n);
    std::cout << std::setw(15) << time << " ";
    std::cout << std::setw(15) << steps << " ";
    std::cout << std::setw(15) << time / steps << std::endl;
}