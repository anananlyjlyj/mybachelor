//Task 8.3: Archimedes algorithm for approximating PI. Implementation by Enes Witwit and Ullrich Koethe.
//Goal: Implement standard algorithm and an expert algorithm and do standard error analysis concerning different basis types (float,double).

#include <iostream>
#include <cmath>
#include <iomanip>

#ifndef M_PI
#    define M_PI     3.14159265358979323846
#endif

using namespace std;

// a)
//Archimedes standard algorithm implementation for basis type float
void archimedes_float(){
    float s = sqrt(2.0); //side length for the inner square
    float t = 2.0f;      //side lenght for the outer square
    cout << setprecision(16);
    cout << "\nFLOAT\n";

    uint64_t n = 4;             //n is the counter for the vertices
    for(int k=0; k<30; ++k)
    {
        float pi_l = 0.5f*n*s;  //circumference of inner polygon
        float pi_u = 0.5f*n*t;  //circumference of outer polygon
        cout << n <<" vertices:  " << pi_l << " (" << (M_PI-pi_l) << "),  "  << pi_u << " (" << (pi_u - M_PI) << ")\n";
        s = sqrt(2.0f - sqrt(4.0f - s*s));  //standard archimedes for inner polygon
        t = (2.0f/t)*(sqrt(4.0f + t*t)  -2.0f); //standard archimedes for outer polygon
        n *= 2;
    }
}

// b)
//Archimedes standard algorithm implementation for basis type double
void archimedes_double(){
    double s = sqrt(2.0); //side length for the inner square
    double t = 2.0;       //side lenght for the outer square
    cout << setprecision(16);
    cout << "\nDOUBLE \n";

    uint64_t n = 4;
    for(int k=0; k<30; ++k)
    {
        double pi_l = 0.5*n*s; //circumference of inner polygon
        double pi_u = 0.5*n*t; //circumference of outer polygon
        cout << n <<" vertices:  " << pi_l << " (" << (M_PI-pi_l) << "),  " << pi_u << " (" <<  (M_PI-pi_l) << ")\n";
        s = sqrt(2.0 - sqrt(4.0 - s*s)); //standard archimedes for inner polygon
        t = (2.0/t)*(sqrt(4.0 + t*t) - 2.0); //standard archimedes for outer polygon
        n *= 2;
    }
}

// c)
//Archimedes expert algorithm implementation for basis type float
void archimedes_float_expert(){
    float s = sqrt(2.0); //side length for the inner square
    float t = 2.0f;      //side lenght for the outer square
    cout << setprecision(16);
    cout << "\nFLOAT EXPERT\n";

    uint64_t n = 4;
    for(int k=0; k<30; ++k)
    {
        float pi_l = 0.5f*n*s; //circumference of inner polygon
        float pi_u = 0.5f*n*t; //circumference of outer polygon
        cout << n <<" vertices:  " << pi_l << " (" << (M_PI-pi_l) << "),  "  << pi_u << " (" << (pi_u - M_PI) << ")\n";
        s = s/sqrt(2.0f + sqrt(4.0f - s*s)); //expert archimedes for inner polygon
        t = 2.0f*t/(sqrt(4.0f + t*t) + 2.0f); //expert archimedes for outer polygon
        n *= 2;
    }
}

//Archimedes expert algorithm implementation for basis type double
void archimedes_double_expert(){
    double s = sqrt(2.0); //side length for the inner square
    double t = 2.0; //side lenght for the outer square
    cout << setprecision(16);
    cout << "\nDOUBLE EXPERT\n";

    uint64_t n = 4;
    for(int k=0; k<30; ++k)
    {
        double pi_l = 0.5*n*s; //circumference of inner polygon
        double pi_u = 0.5*n*t; //circumference of outer polygon
        cout << n <<" vertices:  " << pi_l << " (" << (M_PI-pi_l) << "),  " << pi_u << " (" <<  (M_PI-pi_l) << ")\n";
        s = s/sqrt(2.0 + sqrt(4.0 - s*s)); //expert archimedes for inner polygon
        t = 2.0*t/(sqrt(4.0 + t*t) + 2.0); //expert archimedes for outer polygon
        n *= 2;
    }
}




int main(){

    //Standard archimedes algorithm for basis type float
    archimedes_float();

    //Standard archimedes algorithm for basis type double
    archimedes_double();

    //Expert archimedes algorithm for basis type float
    archimedes_float_expert();

    //Expert archimedes algorithm for basis type double
    archimedes_double_expert();

    return 0;
}
