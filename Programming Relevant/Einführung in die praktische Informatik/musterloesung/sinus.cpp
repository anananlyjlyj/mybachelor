#define _USE_MATH_DEFINES

#include <cmath>
#include <iostream>

// for a nicer look
#include <iomanip>

// (a)
double taylor_sin(double x);
double abs_error(double x, double y);
double to_rad(double degree);
bool taylor_test(double degree);
double rec_for_loop(double degree, double max, double prec);

// (b)
double oump_sin(double x);

// (c)
double my_sin(double x);

// utility functions just for better printing #overkill
void print_tableheader_a();
void print_tableheader_c();
void print_tablerow(double degree, double reference);

// (d)
double my_sin_d(double x);
double normalize(double x);

/*
This code doesn't use:
   - condition-clause
   - loops
*/

int main(int argc, char const *argv[])
{
   // table prints could be a comment in code
   // (a) first part
   std::cout << "\n(a)" << std::endl;
   print_tableheader_a();
   std::cout << std::endl;
   print_tablerow(5,   taylor_sin(to_rad(5)));
   print_tablerow(10,  taylor_sin(to_rad(10)));
   print_tablerow(20,  taylor_sin(to_rad(20)));
   print_tablerow(45,  taylor_sin(to_rad(35)));
   print_tablerow(90,  taylor_sin(to_rad(90)));
   print_tablerow(135, taylor_sin(to_rad(135)));
   print_tablerow(180, taylor_sin(to_rad(180)));
   print_tablerow(225, taylor_sin(to_rad(225)));
   print_tablerow(270, taylor_sin(to_rad(270)));
   print_tablerow(315, taylor_sin(to_rad(315)));

   // (a) second part
   std::cout << std::endl;
   std::cout << "Bis zu einem Winkel von " <<
                rec_for_loop(0, 360, 1e-6) <<
                " Grad kann man die Naeherung benutzen." <<
                std::endl;

   // (c)
   std::cout << "\n(c)" << std::endl;
   print_tableheader_c();
   std::cout << std::endl;
   print_tablerow(5,   my_sin(to_rad(5)));
   print_tablerow(10,  my_sin(to_rad(10)));
   print_tablerow(20,  my_sin(to_rad(20)));
   print_tablerow(45,  my_sin(to_rad(45)));
   print_tablerow(90,  my_sin(to_rad(90)));
   print_tablerow(135, my_sin(to_rad(135)));
   print_tablerow(180, my_sin(to_rad(180)));
   print_tablerow(225, my_sin(to_rad(225)));
   print_tablerow(270, my_sin(to_rad(270)));
   print_tablerow(315, my_sin(to_rad(315)));

   // (d)
   std::cout << "\n(d)" << std::endl;
   print_tableheader_c();
   std::cout << std::endl;
   print_tablerow(5,   my_sin_d(to_rad(5)));
   print_tablerow(10,  my_sin_d(to_rad(10)));
   print_tablerow(20,  my_sin_d(to_rad(20)));
   print_tablerow(45,  my_sin_d(to_rad(45)));
   print_tablerow(90,  my_sin_d(to_rad(90)));
   print_tablerow(135, my_sin_d(to_rad(135)));
   print_tablerow(180, my_sin_d(to_rad(180)));
   print_tablerow(225, my_sin_d(to_rad(225)));
   print_tablerow(270, my_sin_d(to_rad(270)));
   print_tablerow(315, my_sin_d(to_rad(315)));

   print_tablerow(-5,   my_sin_d(to_rad(-5)));
   print_tablerow(-10,  my_sin_d(to_rad(-10)));
   print_tablerow(-20,  my_sin_d(to_rad(-20)));
   print_tablerow(-45,  my_sin_d(to_rad(-45)));
   print_tablerow(-90,  my_sin_d(to_rad(-90)));
   print_tablerow(-135, my_sin_d(to_rad(-135)));
   print_tablerow(-180, my_sin_d(to_rad(-180)));
   print_tablerow(-225, my_sin_d(to_rad(-225)));
   print_tablerow(-270, my_sin_d(to_rad(-270)));
   print_tablerow(-315, my_sin_d(to_rad(-315)));

   print_tablerow(914, my_sin_d(to_rad(914)));

   return 0;
}

// (a)

double pi_2 = 2.0*M_PI;

double taylor_sin(double x)
{return x - std::pow(x, 3)/6.0;}

double abs_error(double x, double y)
{return std::abs(x - y);}

double to_rad(double degree)
{return degree/180.0 * M_PI;}


bool taylor_test(double radians, double prec)
{
   return abs_error(std::sin(radians), taylor_sin(radians)) > prec;
}

double rec_for_loop(double degree, double max, double prec)
{
   return (taylor_test(to_rad(degree), prec) && degree < max) ?
               degree - 1.0:
               rec_for_loop(degree + 1.0, max, prec) ;
}

// (b)
double pump_sin(double sin_third)
{
    return 3.0*sin_third - 4.0*sin_third*sin_third*sin_third;
}

// (c)
// x in radians
// to_rad(9) is the radian value of (a) 2nd part
double my_sin(double x)
{
   return std::abs(x) <= to_rad(9.0) ?
               taylor_sin(x) :
               pump_sin(my_sin(x/3.0));
}

// (d)
// x in radians
double normalize(double x)
{
   // map to interval   0 ... 2*PI
   double y = x - pi_2 * std::floor(x / pi_2);
   // map to interval -PI ... PI
   return (y <= M_PI) ? y
                      : y - pi_2;
}

double my_sin_d(double x)
{
   return my_sin(normalize(x));
}

// utility
// maybe use global constants instead of hardcoded values
void print_tableheader_a()
{
   std::cout << "| " << std::setw(5) << "Grad" << // iomanip
                " | " << std::setw(13) << "std::sin" <<
                " | " << std::setw(13) << "taylor_sin" <<
                " | " << std::setw(13) << "abs error" <<
                " |" << std::endl;
}

void print_tableheader_c()
{
   std::cout << "| " << std::setw(5) << "Grad" << // iomanip
                " | " << std::setw(13) << "std::sin" <<
                " | " << std::setw(13) << "my_sin" <<
                " | " << std::setw(13) << "abs error" <<
                " |" << std::endl;
}

void print_tablerow(double degree, double reference)
{
   const double radians = to_rad(degree), std_sin = std::sin(radians);
   std::cout << "| " << std::setw(5) << degree << // iomanip
                " | " << std::setw(13) << std_sin <<
                " | " << std::setw(13) << reference <<
                " | " << std::setw(13) << abs_error(std_sin, reference) <<
                " |" << std::endl;
}
