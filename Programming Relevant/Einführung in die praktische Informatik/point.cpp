#include <string>
#include <iostream>
#include <cassert>

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
    , y_(0.0)
    {}

    // Konstruktor mit zwei Koordinaten: initialisiere Punkt (x,y)
    Point(double x, double y)
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

// Implementieren Sie hier die arithmetischen Operationen
Point operator+(Point p1, Point p2)
{
    return Point(p1.x() + p2.x(), p1.y() + p2.y());
}
Point operator-(Point p1, Point p2)
{
    return Point(p1.x() - p2.x(), p1.y() - p2.y());
}
Point operator*(Point p1, Point p2)
{
    return Point(p1.x() * p2.x(), p1.y() * p2.y());
}
Point operator/(Point p1, Point p2)
{
    return Point(p1.x() / p2.x(), p1.y() / p2.y());
}
Point operator*(Point p, double s)
{
    return Point(p.x() * s, p.y() * s);
}
Point operator*(double s, Point p)
{
    return Point(p.x() * s, p.y() * s);
}
Point operator/(Point p, double s)
{
    return Point(p.x() / s, p.y() / s);
}
Point operator-(Point p)
{
    return p * (-1.0);
}

void test_Point()
{
    typedef Point P; // neuer kurzer Name für 'Point'

    P p;
    assert(p.x() == 0);
    assert(p.y() == 0);

    // fuegen Sie Tests der arithmetischen Operationen hinzu
    P p1(2.0, 3.0), q(4.0, 5.0), r(0.5, 1.5);
    assert(p1 + q == P(6.0, 8.0));
    assert(p1 + r == P(2.5, 4.5));
    assert(q + r == P(4.5, 5.5));
    assert(q - p1 == P(2.0, 2.0));
    assert(p1 - r == P(1.5, 1.5));
    assert(r - q == P(-3.5, -3.5));
    assert(p1 * q == P(8.0, 15.0));
    assert(p1 * r == P(1.0, 4.5));    
    assert(q * r == P(2.0, 7.5));
    assert(p1 / r == P(4.0, 2.0));
    assert(r / q == P(0.125, 0.3));
    assert(r / p1 == P(0.25, 0.5));
    assert(p1 * 3.0 == P(6.0, 9.0));  
    assert(q * 2.0 == P(8.0, 10.0));   
    assert(r * 4.0 == P(2.0, 6.0));    
    assert(4.0 * p1 == P(8.0, 12.0));
    assert(5.0 * r == P(2.5, 7.5));
    assert(0.3 * q == P(1.2, 1.5));
    assert(p1 / 2.0 == P(1.0, 1.5));  
    assert(q / 0.5 == P(8.0, 10.0));   
    assert(r / 5.0 == P(0.1, 0.3)); 
    assert(-q == P(-4.0, -5.0));
    assert(-p1 == P(-2.0, -3.0));
    assert(-r == P(-0.5, -1.5));
    
    std::cout << "Alle Tests erfolgreich.\n";
}

int main()
{
    test_Point();
}
