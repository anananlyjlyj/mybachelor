#include <string>
#include <iostream>
#include <cassert>

template<typename CoordinateType>

class Point
{
    //typedef double CoordinateType;
  private:
    // die Koordinaten des Punktes
    CoordinateType x_;
    CoordinateType y_;

  public:

    // Standardkonstruktor: initialisiere Punkt (0,0)
    Point()
    : x_(0.0)
    , y_(0.0)
    {}

    // Konstruktor mit zwei Koordinaten: initialisiere Punkt (x,y)
    Point(CoordinateType x, CoordinateType y)
    : x_(x)
    , y_(y)
    {}

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
template <typename CoordinateType>
Point<CoordinateType> operator+(Point<CoordinateType> p1, Point<CoordinateType> p2)
{
    Point<CoordinateType> res(p1.x()+p2.x(), p1.y()+p2.y());
    return res;
}
template <typename CoordinateType>
Point<CoordinateType> operator-(Point<CoordinateType> p1, Point<CoordinateType> p2)
{
    Point<CoordinateType> res(p1.x()-p2.x(), p1.y()-p2.y());
    return res;
}
template <typename CoordinateType>
Point<CoordinateType> operator-(Point<CoordinateType> p)
{
    Point<CoordinateType> res(-p.x(), -p.y());
    return res;
}
template <typename CoordinateType>
Point<CoordinateType> operator*(Point<CoordinateType> p1, Point<CoordinateType> p2)
{
    Point<CoordinateType> res(p1.x()*p2.x(), p1.y()*p2.y());
    return res;
}
template <typename CoordinateType>
Point<CoordinateType> operator*(double s, Point<CoordinateType> p)
{
    Point<CoordinateType> res(s*p.x(), s*p.y());
    return res;
}
template <typename CoordinateType>
Point<CoordinateType> operator*(Point<CoordinateType> p, double s)
{
    Point<CoordinateType> res(p.x()*s, p.y()*s);
    return res;
}
template <typename CoordinateType>
Point<CoordinateType> operator/(Point<CoordinateType> p1, Point<CoordinateType> p2)
{
    Point<CoordinateType> res(p1.x()/p2.x(), p1.y()/p2.y());
    return res;
}
template <typename CoordinateType>
Point<CoordinateType> operator/(Point<CoordinateType> p, double d)
{
    Point<CoordinateType> res(p.x()/d, p.y()/d);
    return res;
}

void test_Point_double()
{
    typedef Point<double> P; // neuer kurzer Name für 'Point'

    P p;
    assert(p.x() == 0);
    assert(p.y() == 0);
    
    double i = 3.0, j = 2.0, k = 4.0;

    P p1(2.0, 3.0), q(4.0, 5.0), r(0.5, 1.5);
    assert(p1 + q == P(6.0, 8.0));
    assert(p1 + r == P(2.5, 4.5));
    assert(q + r == P(4.5, 6.5));
    assert(q - p1 == P(2.0, 2.0));
    assert(p1 - r == P(1.5, 1.5));
    assert(r - q == P(-3.5, -3.5));
    assert(p1 * q == P(8.0, 15.0));
    assert(p1 * r == P(1.0, 4.5));    
    assert(q * r == P(2.0, 7.5));
    assert(p1 / r == P(4.0, 2.0));
    assert(r / q == P(0.125, 0.3));
    assert(r / p1 == P(0.25, 0.5));
    assert(p1 * i == P(6.0, 9.0));  
    assert(q * j == P(8.0, 10.0));   
    assert(r * k == P(2.0, 6.0));    
    assert(k * p1 == P(8.0, 12.0));
    assert((k + 1) * r == P(2.5, 7.5));
    assert((i / 10) * q == P(1.2, 1.5));
    assert(p1 / j == P(1.0, 1.5));  
    assert(q / 0.5 == P(8.0, 10.0));   
    assert(r / 5.0 == P(0.1, 0.3)); 
    assert(-q == P(-4.0, -5.0));
    assert(-p1 == P(-2.0, -3.0));
    assert(-r == P(-0.5, -1.5));
    assert(p1.transpose() == P(3.0, 2.0));
    assert(r.transpose() == P(1.5, 0.5));
    assert(p1.translate(q) == P(6.0, 8.0));
    assert(q.translate(r) == P(4.5, 6.5));

    std::cout << "Alle Tests erfolgreich.\n";
}

void test_Point_int()
{
    typedef Point<int> P;
    
    int i = 3, j = 2, k = 4;

    P p1(2.0, 3.0), q(4.0, 5.0), r(6, 7);
    assert(p1 + q == P(6.0, 8.0));
    assert(p1 + r == P(8, 10));
    assert(q - p1 == P(2.0, 2.0));
    assert(p1 - q == P(-2.0, -2.0));
    assert(p1 * q == P(8.0, 15.0));
    assert(p1 * r == P(12, 21));    
    assert(q / p1 == P(2, 1));
    assert(r / q == P(1, 1));
    assert(p1 * i == P(6.0, 9.0));  
    assert(q * j == P(8.0, 10.0));   
    assert(r * k == P(24, 28));    
    assert(k * p1 == P(8.0, 12.0));
    assert(p1 / j == P(1.0, 1));  
    assert(q / 2 == P(2, 2));    
    assert(-q == P(-4.0, -5.0));
    assert(-p1 == P(-2.0, -3.0));
    assert(p1.transpose() == P(3.0, 2.0));
    assert(r.transpose() == P(7, 6));
    assert(p1.translate(q) == P(6.0, 8.0));
    assert(q.translate(r) == P(10, 12));

    std::cout << "Alle Tests fuer int erfolgreich.\n";
}

int main()
{
    test_Point_double();
    test_Point_int();
}
