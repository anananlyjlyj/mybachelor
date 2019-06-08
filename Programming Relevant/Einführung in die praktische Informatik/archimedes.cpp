#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>

//a)
float floatpi(int n)
{
    float s = std::sqrt(2)f;
    float t = 2f;
    float pi;
    for(;n > 0; n--)
    {
        s = std::sqrt(2 - std::sqrt(4 - s * s));
        t = 2 * (std::sqrt(4 + t * t) - 2) / t;
        pi = (s + t) / 2;
        std::cout << "obere Schaetzwert: " << std::setprecision(16) << n * t / 2 << std::endl;
        std::cout << "untere Schaetzwert: " << std::setprecision(16) << n * s / 2 << std::endl;
        std::cout << "Abweichung: " << std::setprecision(16) << pi / M_PI * 100 << '%' << std::endl;
    }
    return pi;
}

//b)
double doublepi(int n)
{
    double s = std::sqrt(2);
    double t = 2;
    double pi;
    for(;n > 0; n--)
    {
        s = std::sqrt(2 - std::sqrt(4 - s * s));
        t = 2 * (std::sqrt(4 + t * t) - 2) / t;
        pi = (s + t) / 2;
        std::cout << "obere Schaetzwert: " << std::setprecision(16) << n * t / 2 << std::endl;
        std::cout << "untere Schaetzwert: " << std::setprecision(16) << n * s / 2 << std::endl;
        std::cout << "Abweichung: " << std::setprecision(16) << pi / M_PI * 100 << '%' << std::endl;
    }
    return pi;
}

//c)
float floatpi2(int n)
{
    float s = std::sqrt(2)f;
    float t = 2f;
    float pi;
    for(;n > 0; n--)
    {
        s = s / std::sqrt(2 + std::sqrt(4 - s * s));
        t = 2 * t / (std::sqrt(4 + t * t) + 2);
        pi = (s + t) / 2;
        std::cout << "obere Schaetzwert: " << std::setprecision(16) << n * t / 2 << std::endl;
        std::cout << "untere Schaetzwert: " << std::setprecision(16) << n * s / 2 << std::endl;
        std::cout << "Abweichung: " << std::setprecision(16) << pi / M_PI * 100 << '%' << std::endl;
    }
    return pi;
}

double doublepi2(int n)
{
    double s = std::sqrt(2);
    double t = 2;
    double pi;
    for(;n > 0; n--)
    {
        s = s / std::sqrt(2 + std::sqrt(4 - s * s));
        t = 2 * t / (std::sqrt(4 + t * t) + 2);
        pi = (s + t) / 2;
        std::cout << "obere Schaetzwert: " << std::setprecision(16) << n * t / 2 << std::endl;
        std::cout << "untere Schaetzwert: " << std::setprecision(16) << n * s / 2 << std::endl;
        std::cout << "Abweichung: " << std::setprecision(16) << pi / M_PI * 100 << '%' << std::endl;
    }
    return pi;
}

int main()
{
    float pi1 = floatpi(13);
    double pi2 = doublepi(13);
    float pi3 = floatpi2(13);
    double pi4 = doublepi2(13);
    return 0;
}