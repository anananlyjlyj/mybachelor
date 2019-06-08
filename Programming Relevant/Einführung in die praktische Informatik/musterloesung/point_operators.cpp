#include <string>
#include <iostream>
#include <cassert>
#include <cmath> //std::abs für equal_with_tolerance
#define EPS 1e-15

class Point
{
private:
   // die Koordinaten des Punktes
   double x_;
   double y_;

public:

   // Standardkonstruktor: initialisiere Punkt (0,0)
   Point()
   : x_(0.0)
   , y_(0.0){}

   // Konstruktor mit zwei Koordinaten: initialisiere Punkt (x,y)
   Point(double x, double y)
   : x_(x)
   , y_(y){}

   // Getter-Funktionen fuer die Koordinaten
   double x() const
   {
      return (*this).x_;
   }

   double y() const
   {
      return (*this).y_;
   }

   // teste ob zwei Punkte gleich sind
   bool operator==(Point const & other) const
   {
       return (*this).x() == other.x() && (*this).y() == other.y();
   }

   // teste ob zwei Punkte ungleich sind
   bool operator!=(Point const & other) const
   {
       return (*this).x() != other.x() || (*this).y() != other.y();
   }

   bool equal_with_tolerance(Point const & other) const
   {
      return ( std::abs( (*this).x() - other.x() ) < EPS ) && ( std::abs( (*this).y() - other.y() ) < EPS );
   }

   // erzeuge neuen Punkt, desssen x- und y-Koordinate
   // vertauscht sind
   Point transpose() const
   {
      Point res((*this).y(), (*this).x());
      return res;
   }

   // erzeuge neuen Punkt, der um den Vektor v verschoben ist
   Point translate(Point const & v) const
   {
      Point res((*this).x() + v.x(), (*this).y() + v.y());
      return res;
   }
};

// wandle den Punkt in einen String der Form "[x, y]"
std::string to_string(Point const & p)
{
   return "[" + std::to_string(p.x()) + ", " + std::to_string(p.y()) + "]";
}

// Implementieren Sie hier die arithmetischen Operationen

// Aufgabe a)
Point operator+(Point p1, Point p2)
{
   return Point(p1.x() + p2.x(), p1.y() + p2.y());
}

Point operator-(Point p1, Point p2)
{
   return Point(p1.x() - p2.x(), p1.y() - p2.y());
}

//Aufgabe b)
Point operator*(Point p1, Point p2)
{
   return Point(p1.x() * p2.x(), p1.y() * p2.y());
}

Point operator/(Point p1, Point p2)
{
   return Point(p1.x() / p2.x(), p1.y() / p2.y());
}

//Aufgabe c)

Point operator*(double s, Point p)
{
   return Point(s * p.x(), s * p.y());
}

Point operator*(Point p, double s)
{
   return s*p;
}

//Aufgabe d)

Point operator/(Point p, double s)
{
   return Point(p.x()/s, p.y()/s);
}

//Aufgabe e)

Point operator-(Point p)
{
   return Point(-p.x(), -p.y());
}

void test_Point()
{
   typedef Point P; // neuer kurzer Name für 'Point'

   P p;
   assert(p.x() == 0);
   assert(p.y() == 0);

   // fuegen Sie Tests der arithmetischen Operationen hinzu

   P p1(-2.0, -3.0);
   P p2(0.5, 3.33);
   P p3(1.0, 2.0);

   // Aufgabe a)
   assert((p  + p1 ).equal_with_tolerance(p1));
   assert((p2 + p3 ).equal_with_tolerance(P(1.5, 5.33)));
   assert((p1 + p3 ).equal_with_tolerance(P(-1.0, -1.0)));

   assert((p1 - p  ).equal_with_tolerance(p1));
   assert((p3 - p1 ).equal_with_tolerance(P(3.0, 5.0)));
   assert((p3 - p2 ).equal_with_tolerance(P(0.5, -1.33)));
   assert((p3 - p3 ).equal_with_tolerance(p));

   // Aufgabe b)
   assert((p  * p1 ).equal_with_tolerance(p));
   assert((p1 * p2 ).equal_with_tolerance(P(-1.0, -9.99)));
   assert((p3 * p3 ).equal_with_tolerance(P(1.0, 4.0)));

   assert((p  / p1 ).equal_with_tolerance(p));
   assert((p1 / p2 ).equal_with_tolerance(P(-4.0, -0.9009009009009009)));
   assert((p3 / p3 ).equal_with_tolerance(P( 1.0, 1.0)));

   // Aufgabe c)
   assert(( 4.0 * p    ).equal_with_tolerance(p));
   assert((-2.5 * p1   ).equal_with_tolerance(P(5.0, 7.5)));
   assert((17.7 * p2   ).equal_with_tolerance(p2 * 17.7)); //zählt doppelt ;)
   assert((  p3 * 7.5  ).equal_with_tolerance(P(7.5, 15.0)));
   assert((  p2 * 1.2  ).equal_with_tolerance(P(0.6, 3.996)));

   // Aufgabe d)
   assert((p  / 13.37 ).equal_with_tolerance(p));
   assert((p1 /  2    ).equal_with_tolerance(P(-1.0, -1.5)));
   assert((p2 /  2.5  ).equal_with_tolerance(P( 0.2,  1.332)));

   // Aufgabe e)
   assert((-p  ).equal_with_tolerance(p));
   assert((-p1 ).equal_with_tolerance(P( 2.0,  3.0)));
   assert((-p2 ).equal_with_tolerance(-1 * p2));
   assert((-p3 ).equal_with_tolerance(P(-1.0, -2.0)));

   std::cout << "Alle Tests erfolgreich.\n";
}

int main()
{
   test_Point();
}
