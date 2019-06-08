#include <chrono>
#include <vector>

/*
a) 	Minimum: Wenn das Array monoton steigend ist
	f1(n)  = n - 1, g1(n) = n
    Weil gesucht ist schnellst, g1(n) <= f1(n).
b)	Maximum: Wenn das Array monoton fallend ist
	f2(n)  = 1/2 * n * (n - 1), g2(n) = n ^ 2
    Weil gesucht ist der langsamst, g2(n) >= f2(n).
c)	f3(n)  = 1/4 * n * (n - 1), g3(n) = n ^ 2

*/

double insertion_sort_best_time(int n)
{
    std::vector<double> v(n);
    for(int k=0; k<n; ++k)
    {
        v[k] = k;
    }
    auto start = std::chrono::high_resolution_clock::now();
    std::sort(v.begin(), v.end());
    auto stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = stop - start;
    return diff.count();
}

double insertion_sort_worst_time(int n)
{
    std::vector<double> v(n);
    for(int k=0; k<n; ++k)
    {
        v[k] = n - k;
    }
    auto start = std::chrono::high_resolution_clock::now();
    std::sort(v.begin(), v.end());
    auto stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = stop - start;
    return diff.count();
}

double insertion_sort_typical_time(int n)
{
    std::vector<double> v(n);
    for(int k=0; k<n/2; ++k)
    {
        v[k] = k;
    }
    for(int i=n/2; i<n; ++i)
    {
        v[k] = n - k;
    }
    auto start = std::chrono::high_resolution_clock::now();
    std::sort(v.begin(), v.end());
    auto stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = stop - start;
    return diff.count();
}

int main()
{
    std::vector<double> v(3);
    v[0] = insertion_sort_best_time(10);
    v[1] = insertion_sort_worst_time(10);
    v[2] = insertion_sort_typical_time(10);
    std::sort(v);
    
    std::vector<double> v(9);
    v[0] = insertion_sort_best_time(50);
    v[1] = insertion_sort_worst_time(50);
    v[2] = insertion_sort_typical_time(50);
    v[3] = insertion_sort_best_time(100);
    v[4] = insertion_sort_worst_time(100);
    v[5] = insertion_sort_typical_time(100);
    v[6] = insertion_sort_best_time(500);
    v[7] = insertion_sort_worst_time(500);
    v[8] = insertion_sort_typical_time(500);
    return 0;
}
