#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>
#include <cmath>

#include "gifts.txt"

// Aufgabe 1
/////////////////////////////////////////////////
// die 2-dimensionale Punkt-Klasse aus der Vorlesung
class Point
{
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

/////////////////////////////////////////////////
// Implementieren Sie die Rectangle-Klasse.
class Rectangle
{
    Point p0_; // linke untere Ecke
    Point p1_; // rechte obere Ecke

  public:

    // Implementieren Sie die folgenden Konstruktoren.
    Rectangle()
    : p0_(0.0, 0.0)
    , p1_(0.0, 0.0)
    {}

    Rectangle(Point const & p1)
    : p0_(0.0, 0.0)
    , p1_(p1.x(), p1.y())
    {}

    Rectangle(Point const & p0, Point const & p1)
    : p0_(p0.x(), p0.y())
    , p1_(p1.x(), p1.y())
    {}

    // read-only Getter-Funktionen fuer die Member-Variablen
    Point const & p0() const
    {
        return (*this).p0_;
    }

    Point const & p1() const
    {
        return (*this).p1_;
    }

    // Implementieren Sie die folgenden Getter-Funktionen.
    double x0() const // linke x-Koordinate
    {
        return (*this).p0().x();
    }

    double x1() const // rechte x-Koordinate
    {
        return (*this).p1().x();
    }

    double y0() const // untere y-Koordinate
    {
        return (*this).p0().y();
    }

    double y1() const // obere  y-Koordinate
    {
        return (*this).p1().y();
    }

    double width() const  // Breite
    {
        return (*this).x1() - (*this).x0();
    }

    double height() const // Hoehe
    {
         return (*this).y1() - (*this).y0();
    }

    // Implementieren Sie eine Funktion, die genau dann 'true'
    // zurueckgibt, wenn das Rechteck nicht ungueltig ist.
    bool is_valid() const
    {
        if((*this).x1() < (*this).x0() || (*this).y1() < (*this).y0())
            return false;
        return true;
    }

    // Implementieren Sie eine Funktion, die die Flaeche des
    // Rechtecks zurueckgibt, bzw. -1.0, wenn das Rechteck
    // ungueltig ist.
    double area() const
    {
        if((*this).x1() == (*this).x0() || (*this).y1() == (*this).y0())
            return 0.0;
        else if((*this).is_valid())
            return -1.0;
        else
            return (*this).width() * (*this).height();
    }

    // Implementieren Sie eine Funktion, die ein neues Rechteck
    // zurueckgibt, bei dem die x- und y-Koordinaten vertauscht sind.
    Rectangle transpose() const
    {
        Rectangle trans((*this).p0().transpose(), (*this).p1().transpose());
        return trans;
        
    }

    // Implementieren Sie eine Funktion, die ein neues Rechteck
    // zurueckgibt, das um den Vektor v verschoben ist.
    Rectangle translate(Point const & v) const
    {
        Rectangle trans((*this).p0().translate(v), (*this).p1().translate(v));
        return trans;
        
    }

    // Implementieren Sie eine Funktion, die genau dann 'true'
    // zurueckgibt, wenn der Punkt p im Rechteck (*this) enthalten
    // ist. Wenn (*this) ungueltig ist, soll 'false' zurueckgegeben
    // werden.
    bool contains(Point const & p) const
    {
        if((*this).is_valid() && p.x() <= (*this).x1() && p.x() >= (*this).x0() && p.y() <= (*this).y1() && p.y() >= (*this).y0())
            return true;
        return false;
    }

    // Implementieren Sie eine Funktion, die genau dann 'true'
    // zurueckgibt, wenn das Rechteck r im Rechteck (*this) enthalten
    // ist. Wenn (*this) oder r ungueltig sind, soll 'false' zurueckgegeben
    // werden.
    bool contains(Rectangle const & r) const
    {
        if((*this).contains(r.p0()) && (*this).contains(r.p1()) && r.is_valid() && (*this).is_valid())
            return true;
        return false;
    }
};

// Implementieren Sie eine Funktion, die das Rechteck
// in einen String der Form "[x0:x1, y0:y1]" umwandelt.
std::string to_string(Rectangle const & r)
{
    return "[" + std::to_string(r.x0()) + ":" + std::to_string(r.x1()) + ", " + to_string(r.y0()) + ":" + std::to_string(r.y1()) + "]";
}

// Implementieren Sie eine Funktion, die das kleinste Rechteck
// zurueckgibt, das r1 und r2 enthaelt.
Rectangle rectangle_union(Rectangle const & r1, Rectangle const & r2)
{
    if(!r1.is_valid() || !r1.is_valid())
    {
        Rectangle nothing(Point(-1.0, -1.0));
        return nothing;
    }
    Point p0(std::min(r1.x0(), r2.x0()), std::min(r1.y0(), r2.y0()));
    Point p1(std::max(r1.x1(), r2.x1()), std::max(r1.y1(), r2.y1()));
    Rectangle uni(p0, p1);
    return uni;
}

// Implementieren Sie eine Funktion, die den Durchschnitt
// der Rechtecke r1 und r2 zerueckgibt, oder ein beliebiges
// ungueltiges Rechteck, falls r1 und r2 nicht ueberlappen.
Rectangle rectangle_intersection(Rectangle const & r1, Rectangle const & r2)
{
    
    if((!r1.contains(r2.p0()) && !r1.contains(r2.p1())) && !r1.contains(Point(r2.x0(), r2.y1())) && !r1.contains(Point(r2.x1(), r2.y0())) || !r1.is_valid() || !r1.is_valid())
    {
        Rectangle nothing(Point(-1.0, -1.0));
        return nothing;
    }
    Point p0(std::max(r1.x0(), r2.x0()), std::max(r1.y0(), r2.y0()));
    Point p1(std::min(r1.x1(), r2.x1()), std::min(r1.y1(), r2.y1()));
    Rectangle inter(p0, p1);
    return inter;
}

// Implementieren Sie Tests fuer die Rectangle-Klasse.
void testRectangle()
{
    Rectangle r0(Point(3.0, 5.0));

    assert(r0.p0() == Point(0.0, 0.0));
    assert(r0.p1() == Point(3.0, 5.0));

    Rectangle r(Point(1.0, 2.0), Point(3.0, 5.0));

    assert(r.x0() == 1.0);

    // Fuegen Sie weitere Tests entsprechend der Aufgabe hinzu.
    // b)Tests
    Rectangle r1;
    assert(r1.x0() == 0.0);
    assert(r1.x1() == 0.0);
    assert(r1.y0() == 0.0);
    assert(r1.y1() == 0.0);
    
    Rectangle r2(Point(2.0,4.0));
    assert(r2.x0() == 0.0);
    assert(r2.x1() == 2.0);
    assert(r2.y0() == 0.0);
    assert(r2.y1() == 4.0);
    
    Rectangle r3(Point(1.0, 2.0), Point(3.0,4.0));
    assert(r3.x0() == 1.0);
    assert(r3.x1() == 3.0);
    assert(r3.y0() == 2.0);
    assert(r3.y1() == 4.0);
    // c)Tests
    assert(to_string(r1) == "[0.0:0.0, 0.0:0.0]");
    assert(to_string(r2) == "[0.0:2.0, 0.0:4.0]");
    assert(to_string(r3) == "[1.0:3.0, 2.0:4.0]");
    // d)Tests
    assert(r2.width() == 2.0);
    assert(r2.height() == 4.0);
    assert(r3.width() == 2.0);
    assert(r3.height() == 2.0);
    // e)Tests
    assert(r3.is_valid());
    assert(r3.area() == 4.0);
    Rectangle r4(Point(1.0, 1.0), Point(0.0, 2.0));
    assert(!r4.is_valid());
    assert(r4.area() == -1.0);
    Rectangle r5(Point(0.0, 2.0));
    assert(r5.is_valid());
    assert(r5.area() == 0.0);
    // f)Tests
    assert(r3.transpose().p0() == Point(2.0, 1.0));
    assert(r3.transpose().p1() == Point(4.0, 3.0));
    assert(r3.translate(Point(1.0, 1.0)).p0() == Point(2.0, 3.0));
    assert(r3.translate(Point(1.0, 1.0)).p1() == Point(4.0, 5.0));
    // g)Tests
    assert(r3.contains(Point(2.0, 2.0)));
    assert(!r3.contains(Point(2.0, 4.0)));    
    assert(!r5.contains(Point(0.0, 1.0)));
    assert(!r2.contains(r3));
    Rectangle r6(Point(4.0, 4.0));
    assert(r6.contains(r3));
    assert(!r3.contains(r6));
    // h)Tests
    assert(rectangle_union(r2, r3).contains(r2));
    assert(rectangle_union(r2, r3).contains(r3));
    assert(rectangle_intersection(r2, r3).p0() == Point(1.0, 2.0));
    assert(rectangle_intersection(r2, r3).p1() == Point(2.0, 4.0));
    assert(rectangle_intersection(r3.transpose(), r3).p0() == Point(2.0, 2.0));
    assert(rectangle_intersection(r3.transpose(), r3).p1() == Point(3.0, 3.0));
    assert(!rectangle_union(r4, r3).is_valid());
    assert(!rectangle_intersection(r4, r3).is_valid());
    assert(!rectangle_intersection(r1, r3).is_valid());
    

    std::cout << "alle Rectangle-Tests erfolgreich\n";
}

// Aufgabe 2
//////////////////////////////////////////////////////////////
// Schritt 2
double bssf_score(Rectangle const& free, Rectangle const& obj)          
{
    double restwidth = free.width() - obj.width();
    double restheight = free.height() - obj.height();
    double big_number = 1e300;
    if(restwidth < 0 || restheight < 0)
        return big_number;
    else
        return std::min(restwidth, restheight);
}

int main()
{
    testRectangle();
    
    // Schritt 1
    std::vector<Rectangle> to_be_placed = gifts;
    std::vector<Rectangle> already_placed;
    std::vector<Rectangle> free_rectangles (1, table);
    
    while(1)
    {
        // Schritt 3    
        double bestscore = 1e300;
        int best_obj = -1;
        int best_free = -1;
        
        for(int i = 0; i < to_be_placed.size(); i++)            
        {
            for(int j = 0; j < free_rectangles.size(); j++)
            {
                double score = bssf_score(free_rectangles[j], to_be_placed[i]);
                if(score < bestscore)
                {
                    best_obj = i;
                    best_free = j;
                    bestscore = score;                
                }
        
            }
            
        }   
        // Schritt 4
        bool iftrans = false;    // ob das Objekt transponiert werden soll, um besten Score zu bekommen
        
        for(int k = 0; k < to_be_placed.size(); k++)            
        {
            Rectangle trans = to_be_placed[k].transpose();
            for(int l = 0; l < free_rectangles.size(); l++)
            {
                double score2 = bssf_score(free_rectangles[l], trans);
                if(score2 < bestscore)
                {
                    best_obj = k;
                    best_free = l;
                    bestscore = score2;
                    iftrans = true;
                }
        
            }
            
        }
        
        // Schritt 5
        if(bestscore == 1e300)
            break;
        
        Rectangle bestgift = to_be_placed[best_obj];
        Rectangle bestplace = to_be_placed[best_obj];
        if(iftrans)
            bestgift = bestgift.transpose();
        Point move = (bestplace.x0() - bestgift.x0(), bestplace.y0() - bestgift.y0());
        Rectangle done = bestgift.translate(move);
        already_placed.push_back(done);
        to_be_placed.erase(to_be_placed.begin() + best_obj);
        free_rectangles.erase(free_rectangles.begin() + best_free);
        
        if(bestplace.width() < bestplace.height())  // horizontale Schnitt
        {
            Point new1p0(bestplace.x0(), bestplace.y0() + bestgift.height());
            Rectangle newrec1(new1p0, bestplace.p1());
            Point new2p0(bestplace.x0() + bestgift.width(), bestplace.y0());
            Point new2p1(bestplace.x1(), bestplace.y0() + bestgift.height());
            Rectangle newrec2(new2p0, new2p1);
            free_rectangles.push_back(newrec1);
            free_rectangles.push_back(newrec2);
        }
        else                                        // vertikale Schnitt
        {
            Point new1p0(bestplace.x0(), bestplace.y0() + bestgift.height());
            Point new1p1(bestplace.x0() + bestgift.width(), bestplace.y1());        
            Rectangle newrec1(new1p0, new1p1);
            Point new2p0(bestplace.x0() + bestgift.width(), bestplace.y0());
            Rectangle newrec2(new2p0, bestplace.p1());
            free_rectangles.push_back(newrec1);
            free_rectangles.push_back(newrec2);
        }
        
        // Schnitt 6
        for(int t = 0; t < free_rectangles.size(); t++)
        {
            for(int e = t; e < free_rectangles.size(); e++)
            {
                Rectangle uni = rectangle_union(free_rectangles[t], free_rectangles[e]);
                if(uni.is_valid() && uni.area() == free_rectangles[t].area() + free_rectangles[e].area())   // ob die Vereinigung exakt die beiden urspruenglichen Rechtecke enthaelt
                {
                    free_rectangles.erase(free_rectangles.begin() + t);
                    free_rectangles.erase(free_rectangles.begin() + e);
                    already_placed.push_back(uni);
                }
            }
        }
        
        // Schnitt 7
        for(int a = 0; a < free_rectangles.size(); a++)
        {
            if(free_rectangles[a].width() == 30 && free_rectangles[a].height() == 30)
            {
                free_rectangles.erase(free_rectangles.begin() + a);
                already_placed.push_back(tree_stand);
            }
                
        }
        
        // Schnitt 8
        for(int b = 0; b < already_placed.size(); b++)
        {
            assert(table.contains(already_placed[b]));
            for(int g = b; g < already_placed.size(); g++)
            {
                assert(!rectangle_intersection(already_placed[g], already_placed[b]).is_valid());
            }
            std::cout << to_string(already_placed[b]) << std::endl;
        }
        double rest_area = 0;
        for(int c = 0; c < free_rectangles.size(); c++)
        {
            rest_area += free_rectangles[c].area();
        }
        std::cout << rest_area << std::endl;
    }
    
    
    return 0;
}