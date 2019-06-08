#include <iostream>
#include <cmath>

bool is_square(int n)
{
    int n_4 = n % 4; // Rest bei Division durch 4
    if (n_4 == 2 || n_4 == 3)
    {
        // keine Quadratzahl hat Rest 2 oder 3
        return false;
    }
    double sqrt_n = std::sqrt(n);        // reellwertige Wurzel
    return sqrt_n == std::floor(sqrt_n); // ist die Wurzel eine ganze Zahl?
}

void pythagorean_triple(int bmax)
{
    for (int b = 2; b <= bmax; ++b)
    {
        for (int a = 1; a < b; ++a)
        {
            int c_sq = a*a + b*b;
            if (is_square(c_sq))
            {
                std::cout << a << " " << b << " " << std::sqrt(c_sq) << std::endl;
            }
        }
    }
}

int main()
{
    pythagorean_triple(400);
    return 0;
}