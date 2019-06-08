
#include <iostream>
#include <cassert>
#include <cmath>

double sq(double x)
{
  return x * x;
}

/*
Warum ist es keine gute Idee, bei geradem n zwei rekursive Aufrufe von power zu verwenden?
=> Man wuerde dann zweimal x^(n/2) berechnen, obwohl beide Male das gleiche Ergebnis rauskommen muss.
Dadurch verliert man wieder den Vorteil, weniger Multiplikationen zu brauchen als
bei der naiven n-fachen Multiplikation.
*/
double power(double x, int n)
{
  assert(n > 0);
  return (n == 1) ? x :
                    (n % 2 == 0) ? sq(power(x, n/2)) : x * power(x, n-1);
}

int main()
{

  std::cout.precision(16);
  std::cout << "x=" << -1.3  << " n = " << 3
            << ": std::pow: " << std::pow(-1.3, 3)
            << ", power: " << power(-1.3, 3) << "\n";
  std::cout << "x=" << -1.3  << " n = " << 4
            << ": std::pow: " << std::pow(-1.3, 4)
            << ", power: " << power(-1.3, 4) << "\n";
  std::cout << "x=" <<  2 << " n = " << 1
            << ": std::pow: " << std::pow(2, 1)
            << " power: " << power(2,1) << "\n";
  std::cout << "x=" << 0  << " n = " << 100
            << ": std::pow: " << std::pow(0, 100)
            << ", power: " << power(0,100) << "\n";
  std::cout << "x=" << 12.0542  << " n = " << 50
            << ": std::pow: " << std::pow(12.0542, 50)
            << ", power: " << power(12.0542, 50) << "\n";
  std::cout << "x=" << 12.0542  << " n = " << 51
            << ": std::pow: " << std::pow(12.0542, 51)
            << ", power: " << power(12.0542, 51) << "\n";
  std::cout << "x=" << 286.1  << " n = " << 7
            << ": std::pow: " << std::pow(286.1, 7)
            << ", power: " << power(286.1, 7) << "\n";
  std::cout << "x=" << 286.1  << " n = " << 8
            << ": std::pow: " << std::pow(286.1, 8)
            << ", power: " << power(286.1, 8) << "\n";

  return 0;
}
/* Programmausgabe:
x=-1.3 n = 3: std::pow: -2.197, power: -2.197000000000001
x=-1.3 n = 4: std::pow: 2.856100000000001, power: 2.856100000000001
x=2 n = 1: std::pow: 2 power: 2
x=0 n = 100: std::pow: 0, power: 0
x=12.0542 n = 50: std::pow: 1.140038831578683e+54, power: 1.140038831578685e+54
x=12.0542 n = 51: std::pow: 1.374225608361576e+55, power: 1.374225608361578e+55
x=286.1 n = 7: std::pow: 1.569007446088091e+17, power: 1.569007446088091e+17
x=286.1 n = 8: std::pow: 4.488930303258029e+19, power: 4.488930303258028e+19

Die Ergebnisse von pow und power sind also extrem aehnlich, Unterschiede schleichen
sich vor allem bei hohen Potenzen langsam ein (Rundungsfehler durch mehrmaliges Multiplizieren)
*/

