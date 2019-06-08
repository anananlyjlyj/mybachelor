#include <iostream>
#include <sstream>
#include <vector>
#include <array>
#include <algorithm>
#include <cassert>
#include <string>

class Point
{
    // die Koordinaten des Punktes als Array der Laenge 2
    std::array<double, 2> data_;

  public:

    // Standardkonstruktor: initialisiere Punkt (0,0)
    Point()
    : data_{0.0, 0.0}
    {}

    // Konstruktor mit zwei Koordinaten: initialisiere Punkt (x,y)
    Point(double x, double y)
    : data_{x, y}
    {}

    // Getter-Funktionen fuer die Koordinaten
    double x() const
    {
        return (*this).data_[0];
    }

    double y() const
    {
        return (*this).data_[1];
    }

    // erzeuge neuen Punkt, der um den Vektor v verschoben ist
    Point translate(Point const & v) const
    {
        return Point((*this).x() + v.x(), (*this).y() + v.y());
    }

    // erzeuge neuen Punkt, desssen x- und y-Koordinate
    // vertauscht sind
    Point transpose() const
    {
        return Point((*this).y(), (*this).x());
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
};

// wandle den Punkt in einen String der Form "[x, y]"
std::string to_string(Point const & p)
{
    return "[" + std::to_string(p.x()) + ", " + std::to_string(p.y()) + "]";
}

class Rectangle
{
    Point p0_, p1_;

  public:

    Rectangle()
    {
        // this can be empty since the points are default constructed to (0, 0)
    }

    Rectangle(Point const & p1)
    : p1_(p1)   // p0_ is again default constructed
    {}

    Rectangle(Point const & p0, Point const & p1)
    : p0_(p0), p1_(p1)
    {}

    Point const & p0() const
    {
        return (*this).p0_;
    }

    Point const & p1() const
    {
        return (*this).p1_;
    }

    double x0() const
    {
        return p0_.x();
    }

    double x1() const
    {
        return p1_.x();
    }

    double y0() const
    {
        return p0_.y();
    }

    double y1() const
    {
        return p1_.y();
    }

    double width() const
    {
        return x1() - x0();
    }

    double height() const
    {
        return y1() - y0();
    }

    double short_side() const
    {
        return std::min(width(), height());
    }

    double long_side() const
    {
        return std::max(width(), height());
    }

    bool is_valid() const
    {
        return x0() <= x1() && y0() <= y1();
    }

    double area() const
    {
        return is_valid()? width() * height() : -1;
    }

    Rectangle transpose() const
    {
        return Rectangle(p0_.transpose(), p1_.transpose());
    }

    Rectangle translate(Point const & v) const
    {
        return Rectangle(p0_.translate(v), p1_.translate(v));
    }

    bool contains(Point const & p) const
    {
        return p.x() >= x0() && p.x() <= x1() && p.y() >= y0() && p.y() <= y1();
    }
    
    bool contains(Rectangle const & r) const
    {
        return is_valid() && r.is_valid() && contains(r.p0()) && contains(r.p1());
    }
};

std::string to_string(Rectangle const & r)
{
    // using "to_string" for double results in: [0.0000000000:0.0000000000, ...]
    std::stringstream stream;
    stream << "[" << r.x0() << ":" << r.x1() << ", " << r.y0() << ":" << r.y1() << "]";
    return stream.str();
}


Rectangle rectangle_union(Rectangle const & r1, Rectangle const & r2)
{
    Point lower_left(std::min(r1.x0(), r2.x0()), std::min(r1.y0(), r2.y0()));
    Point upper_right(std::max(r1.x1(), r2.x1()), std::max(r1.y1(), r2.y1()));
    
    return Rectangle(lower_left, upper_right);
}

// erzeuge den Durchschnitt der Rechtecke r1 und r2
Rectangle rectangle_intersection(Rectangle const & r1, Rectangle const & r2)
{
    Point lower_left(std::max(r1.x0(), r2.x0()), std::max(r1.y0(), r2.y0()));
    Point upper_right(std::min(r1.x1(), r2.x1()), std::min(r1.y1(), r2.y1()));
    
    return Rectangle(lower_left, upper_right);
}

bool equal(Rectangle const & r1, Rectangle const & r2)
{
    return r1.x0() == r2.x0() && r1.x1() == r2.x1() && r1.y0() == r2.y0() && r1.y1() == r2.y1();
}

// Testcode fuer die Rectangle-Klasse
void testRectangle()
{
    Rectangle r0(Point(3.0, 5.0));

    assert(r0.p0() == Point(0.0, 0.0));
    assert(r0.p1() == Point(3.0, 5.0));

    Rectangle r(Point(1.0, 2.0), Point(3.0, 5.0));

    assert(r.x0() == 1.0);

    // b)
    
    assert(to_string(Rectangle())                               == "[0:0, 0:0]");
    assert(to_string(Rectangle(Point(1, 2)))                    == "[0:1, 0:2]");
    assert(to_string(Rectangle(Point(-1, -2), Point(0, 0)))     == "[-1:0, -2:0]");
    assert(to_string(Rectangle(Point(-1.23, 4.56), Point(7.89, 10.1112)))
        == "[-1.23:7.89, 4.56:10.1112]");
    assert(to_string(Rectangle(Point(-1, -2))) == "[0:-1, 0:-2]");
    assert(to_string(Rectangle(Point(1, 2), Point(2, 1))) == "[1:2, 2:1]");
    
    // c)
    
    Rectangle zero;
    assert(zero.width() == 0);
    assert(zero.height() == 0);
    assert(zero.long_side() == 0);
    assert(zero.short_side() == 0);
    
    Rectangle high(Point(1, 2), Point(3, 6));
    assert(high.width() == 2);
    assert(high.height() == 4);
    assert(high.short_side() == 2);
    assert(high.long_side() == 4);
    
    Rectangle wide(Point(1, 2), Point(4, 4));
    assert(wide.width() == 3);
    assert(wide.height() == 2);
    assert(wide.short_side() == 2);
    assert(wide.long_side() == 3);
    
    Rectangle bad(Point(-1, -2));
    assert(bad.width() == -1);
    assert(bad.height() == -2);
    assert(bad.short_side() == -2);
    assert(bad.long_side() == -1);
    
    // d)
    
    Rectangle x_bad(Point(-1, 2));
    Rectangle y_bad(Point(1, -2));
    Rectangle x_line(Point(1, 0));
    Rectangle y_line(Point(0, 1));
    
    assert(zero.is_valid());
    assert(x_line.is_valid());
    assert(y_line.is_valid());
    assert(high.is_valid());
    assert(wide.is_valid());
    assert(!bad.is_valid());
    assert(!x_bad.is_valid());
    assert(!y_bad.is_valid());
    
    assert(zero.area() == 0);
    assert(x_line.area() == 0);
    assert(y_line.area() == 0);
    assert(bad.area() == -1);
    assert(x_bad.area() == -1);
    assert(y_bad.area() == -1);
    assert(high.area() == 8);
    assert(wide.area() == 6);
    
    // e)
    
    Rectangle on_diagonal(Point(3, 3), Point(6, 6));
    Rectangle high_transposed(Point(2, 1), Point(6, 3));
    Rectangle one(Point(1, 1), Point(1, 1));
    Rectangle high_plus_23(Point(3, 5), Point(5, 9));
    
    assert(equal(zero.transpose(), zero));
    assert(equal(on_diagonal.transpose(), on_diagonal));
    assert(equal(x_line.transpose(), y_line));
    assert(equal(y_line.transpose(), x_line));
    assert(equal(high.transpose(), high_transposed));
   
    assert(equal(zero.translate(Point(0, 0)), zero));
    assert(equal(high.translate(Point(0, 0)), high));
    assert(equal(wide.translate(Point(0, 0)), wide));
    assert(equal(bad.translate(Point(0, 0)), bad));
    assert(equal(zero.translate(Point(1, 1)), one));
    assert(equal(high.translate(Point(2, 3)), high_plus_23));
    assert(equal(high_plus_23.translate(Point(-2, -3)), high));
    
    // f)
    
    assert(zero.contains(Point(0, 0)));
    assert(!zero.contains(Point(1, 0)));
    assert(high.contains(high.p0()));
    assert(high.contains(high.p1()));
    assert(!high.contains(Point(100, 100)));
    assert(x_line.contains(x_line.p0()));
    assert(!x_line.contains(Point(100, 0)));
    assert(!x_line.contains(Point(0, 100)));
    assert(x_line.contains(x_line.p1()));
    assert(high.contains(Point(2, 2)));
    assert(high.contains(Point(2, 3)));
    assert(!high.contains(Point(2, 100)));
    
    // wow, so many cases
    
    assert(zero.contains(zero));
    assert(x_line.contains(x_line));
    assert(y_line.contains(y_line));
    assert(high.contains(high));
    
    Point p0(0, 0);
    Point p1(1, 1);
    Point p2(2, 2);
    Point p01(0, 1);
    Point pm11(-1, 1);
    Point p12(1, 2);
    Point p3(3, 3);
    
    
    //  _____
    // |  _  |
    // | |_| |
    // |_____|
    assert(Rectangle(p0, p3).contains(Rectangle(p1, p2)));
    assert(!Rectangle(p1, p2).contains(Rectangle(p0, p3)));
    
    //  _____
    // |     |
    // |_    |
    // |_|___|
    assert(Rectangle(p0, p3).contains(Rectangle(p0, p1)));
    assert(!Rectangle(p0, p1).contains(Rectangle(p0, p3)));
    
    //  ___ _
    // |   |_|
    // |     |
    // |_____|
    assert(Rectangle(p0, p3).contains(Rectangle(p2, p3)));
    assert(!Rectangle(p2, p3).contains(Rectangle(p0, p3)));
    
    //  _____
    // |_    |
    // |_|   |
    // |_____|
    assert(Rectangle(p0, p3).contains(Rectangle(p01, p12)));
    assert(!Rectangle(p01, p12).contains(Rectangle(p0, p3)));
    
    //    _____
    //  _|_    |
    // |___|   |
    //   |_____|
    assert(!Rectangle(p0, p3).contains(Rectangle(pm11, p12)));
    assert(!Rectangle(p01, p12).contains(Rectangle(p0, p3)));
   
    //    ___
    //  _|_  |
    // | |_|_|
    // |___|
    assert(!Rectangle(p0, p2).contains(Rectangle(p1, p3)));
    assert(!Rectangle(p1, p3).contains(Rectangle(p0, p2)));
    
    // g)
    
    assert(equal(rectangle_union(zero, zero), zero));
    assert(equal(rectangle_intersection(zero, zero), zero));
    assert(equal(rectangle_union(high, high), high));
    assert(equal(rectangle_intersection(high, high), high));
    assert(equal(rectangle_union(x_line, x_line), x_line));
    assert(equal(rectangle_intersection(x_line, x_line), x_line));
    
    assert(equal(rectangle_union(Rectangle(p0, p1), Rectangle(p1, p2)), Rectangle(p0, p2)));
    assert(equal(rectangle_union(Rectangle(p0, p1), Rectangle(p2, p3)), Rectangle(p0, p3)));
    assert(equal(rectangle_union(Rectangle(p1, p2), Rectangle(p0, p1)), Rectangle(p0, p2)));
    assert(equal(rectangle_union(Rectangle(p2, p3), Rectangle(p0, p1)), Rectangle(p0, p3)));
    
    assert(equal(rectangle_intersection(Rectangle(p0, p1), Rectangle(p1, p2)), Rectangle(p1, p1)));
    assert(!rectangle_intersection(Rectangle(p0, p1), Rectangle(p2, p3)).is_valid());
    assert(equal(rectangle_intersection(Rectangle(p1, p2), Rectangle(p0, p1)), Rectangle(p1, p1)));
    assert(!rectangle_intersection(Rectangle(p2, p3), Rectangle(p0, p1)).is_valid());
    
    
    Rectangle high_union_wide = rectangle_union(high, wide);
    Rectangle wide_union_high = rectangle_union(high, wide);
    Rectangle high_inter_wide = rectangle_intersection(high, wide);
    Rectangle wide_inter_hide = rectangle_intersection(high, wide);
    assert(high_union_wide.contains(wide));
    assert(high_union_wide.contains(high));
    assert(high.contains(high_inter_wide));
    assert(wide.contains(high_inter_wide));
    assert(equal(high_union_wide, wide_union_high));
    assert(equal(high_inter_wide, wide_inter_hide));
    
    Rectangle x_union_y = rectangle_union(x_line, y_line);
    Rectangle y_union_x = rectangle_union(y_line, x_line);
    Rectangle x_inter_y = rectangle_intersection(x_line, y_line);
    Rectangle y_inter_x = rectangle_intersection(y_line, x_line);
    assert(x_union_y.contains(x_line));
    assert(x_union_y.contains(y_line));
    assert(x_line.contains(x_inter_y));
    assert(y_line.contains(x_inter_y));
    assert(equal(x_union_y, y_union_x));
    assert(equal(x_inter_y, y_inter_x));
    
    std::cout << "alle Rectangle-Tests erfolgreich\n";
}

int main()
{
    testRectangle();
}