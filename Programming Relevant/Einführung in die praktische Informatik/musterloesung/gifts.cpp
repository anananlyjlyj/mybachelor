#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <cassert>
#include <string>

typedef int value_type;

class Point
{
    std::array<value_type, 2> data_;

  public:

    Point(value_type x = 0, value_type y = 0)
    : data_{x, y}
    {}

    value_type x() const
    {
        return data_[0];
    }

    value_type y() const
    {
        return data_[1];
    }

    Point translate(Point const & p) const
    {
        return Point(data_[0] + p.x(), data_[1] + p.y());
    }

    Point transpose() const
    {
        return Point(data_[1], data_[0]);
    }
};

std::string to_string(Point const & p)
{
    return "[" + std::to_string(p.x()) + ", " + std::to_string(p.y()) + "]";
}

class Rectangle
{
    Point p0_, p1_;

  public:

    Rectangle()
    : p0_()
    , p1_()
    {}

    Rectangle(Point const & p1)
    : p0_()
    , p1_(p1)
    {}

    Rectangle(Point const & p0, Point const & p1)
    : p0_(p0)
    , p1_(p1)
    {}

    bool contains(Rectangle const & r) const
    {
        return p0_.x() <= r.p0_.x() && p0_.y() <= r.p0_.y() &&
               r.p1_.x() <= p1_.x() && r.p1_.y() <= p1_.y();
    }

    bool is_valid() const
    {
        return width() >= 0 && height() >= 0;
    }

    Point const & p0() const { return p0_; }
    Point const & p1() const { return p1_; }

    value_type x0() const { return p0_.x(); }
    value_type x1() const { return p1_.x(); }
    value_type y0() const { return p0_.y(); }
    value_type y1() const { return p1_.y(); }

    value_type width() const
    {
        return p1_.x() - p0_.x();
    }

    value_type height() const
    {
        return p1_.y() - p0_.y();
    }

    value_type short_side() const
    {
        return std::min(width(), height());
    }

    value_type long_side() const
    {
        return std::max(width(), height());
    }

    value_type area() const
    {
        if(!is_valid())
            return -1;
        return width()*height();
    }

    Rectangle translate(Point const & p) const
    {
        return Rectangle(p0_.translate(p), p1_.translate(p));
    }

    Rectangle transpose() const
    {
        return Rectangle(p0_.transpose(), p1_.transpose());
    }
};

std::string to_string(Rectangle const & r)
{
    return "[" + std::to_string(r.x0()) + ":" + std::to_string(r.x1()) +
           "]x[" + std::to_string(r.y0()) + ":" + std::to_string(r.y1()) + "]";
}

Rectangle intersection(Rectangle const & r1, Rectangle const & r2)
{
    if(!r1.is_valid())
        return r1;
    if(!r2.is_valid())
        return r2;
    Point p0(std::max(r1.x0(), r2.x0()), std::max(r1.y0(), r2.y0()));
    Point p1(std::min(r1.x1(), r2.x1()), std::min(r1.y1(), r2.y1()));
    return Rectangle(p0, p1);
}

Rectangle set_union(Rectangle const & r1, Rectangle const & r2)
{
    if(!r1.is_valid())
        return r1;
    if(!r2.is_valid())
        return r2;
    Point p0(std::min(r1.x0(), r2.x0()), std::min(r1.y0(), r2.y0()));
    Point p1(std::max(r1.x1(), r2.x1()), std::max(r1.y1(), r2.y1()));
    return Rectangle(p0, p1);
}

typedef std::vector<Rectangle> RArray;
double big_number = 1e300;

bool can_merge(Rectangle const & r1, Rectangle const & r2)
{
    // check if two rectangles share a side
    return set_union(r1, r2).area() == r1.area() + r2.area();
}

double bssf_score(Rectangle const & free_rectangles, Rectangle const & insert)
{
    // compute score according to BSSF rule
    // return a big number if 'insert' doesn't fit into 'free_rectangles'
    double score = std::min(free_rectangles.width() - insert.width(), free_rectangles.height() - insert.height());
    if(score < 0.0)
        return big_number;
    else
        return score;
}

RArray insert_rectangle(Rectangle const & free_rectangles, Rectangle const & insert)
{
    // assume that insert has already been translated and transposed

    RArray res;
    // split remaining free_rectangles space according to SAS rule
    if(free_rectangles.width() < free_rectangles.height())
    {
        res.push_back({{free_rectangles.x0(), insert.y1()}, {free_rectangles.x1(), free_rectangles.y1()}});
        res.push_back({{insert.x1(), free_rectangles.y0()}, {free_rectangles.x1(), insert.y1()}});
    }
    else
    {
        res.push_back({{insert.x1(), free_rectangles.y0()}, {free_rectangles.x1(), free_rectangles.y1()}});
        res.push_back({{free_rectangles.x0(), insert.y1()}, {insert.x1(), free_rectangles.y1()}});
    }
    return res; // return remaining free_rectangles space rectangles
}

#include "gifts.txt"

int main()
{
    std::cout << "table:\n" << "  " << to_string(table) << "\n";
    std::cout << "tree stand:\n" << "  " << to_string(tree_stand) << "\n";

    // the initial free_rectangles space is the entire table
    RArray free_rectangles = {table};

    // the objects to be placed
    std::cout << "gifts:\n";
    double area = 0.0;
    for(auto r: gifts)
    {
        area += r.area();
        std::cout << "  " << to_string(r) << "\n";
    }

    std::cout << "available area: " << table.area() << "\n";
    std::cout << "tree stand area: " << tree_stand.area() << "\n";
    std::cout << "gifts' total area: " << area << "\n";

    RArray to_be_placed = gifts;
    to_be_placed.push_back(tree_stand);

    // the completed objects (initially empty)
    RArray already_placed;

    // place objects with GUILLOTINE-BSSF-SAS-RM-DESCSS algorithm
    // see: J. Jylaenki: A Thousand Ways to Pack the Bin, 2010

    // place objects
    while(to_be_placed.size() > 0)
    {
        std::cout << "placing gift " << already_placed.size() << "\n";

        // find the pair [free_index, gift_index] with minimal score
        double min_score = big_number;
        int gift_index = 0;
        int free_index = 0;
        bool transposed = false;
        for(int g=0; g < to_be_placed.size(); ++g)
        {
            for(int f=0; f < free_rectangles.size(); ++f)
            {
                // try upright placement
                double score = bssf_score(free_rectangles[f], to_be_placed[g]);
                if(score < min_score)
                {
                    min_score = score;
                    gift_index = g;
                    free_index = f;
                    transposed = false;
                }
                // try transposed placement
                score = bssf_score(free_rectangles[f], to_be_placed[g].transpose());
                if(score < min_score)
                {
                    min_score = score;
                    gift_index = g;
                    free_index = f;
                    transposed = true;
                }
            }
        }
        std::cout << "  min score: " << min_score << "\n";
        if(min_score == big_number)
        {
            // std::cout << "infeasible problem, giving up\n";
            break;
        }

        // get object at 'gift_index' and transpose when this gave a better score
        auto r1 = transposed
                    ? to_be_placed[gift_index].transpose()
                    : to_be_placed[gift_index];

        // move r1 to lower left corner of free_rectangles space at 'free_index'
        auto r2 = r1.translate(free_rectangles[free_index].p0());

        // insert r2 and get remaining free_rectangles space
        auto remaining = insert_rectangle(free_rectangles[free_index], r2);

        // add r2 to array of 'already_placed' objects
        already_placed.push_back(r2);

        // remove object from array 'to_be_placed'
        to_be_placed.erase(to_be_placed.begin() + gift_index);

        // update free_rectangles space
        free_rectangles[free_index] = remaining[0];
        free_rectangles.push_back(remaining[1]);

        // optimize free_rectangles space according to RM rule
        // (join free_rectangles regions that share a side)
        for(int f1=0; f1<free_rectangles.size()-1; ++f1)
        {
            for(int f2=f1+1; f2<free_rectangles.size(); )
            {
                if(can_merge(free_rectangles[f1], free_rectangles[f2]))
                {
                    free_rectangles[f1] = set_union(free_rectangles[f1], free_rectangles[f2]);
                    free_rectangles.erase(free_rectangles.begin()+f2);
                }
                else
                {
                    ++f2;
                }
            }
        }
    }

    // output the solutions
    std::cout << "final placement:\n";
    for(auto r: already_placed)
    {
        std::cout << "  " << to_string(r) << "\n";
    }
    std::cout << "remaining free space:\n";
    area = 0.0;
    for(auto r: free_rectangles)
    {
        std::cout << "  " << to_string(r) << "\n";
        area += r.area();
    }
    std::cout << "  (area: " << area << ")\n";

    // check correctness
    bool tree_found = false;
    for(int k=0; k<already_placed.size(); ++k)
    {
        assert(table.contains(already_placed[k]));
        for(int j=k+1; j<already_placed.size(); ++j)
        {
            assert(intersection(already_placed[k], already_placed[j]).area() <= 0);
        }
        if(already_placed[k].width() == tree_stand.width() &&
           already_placed[k].height() == tree_stand.height())
            tree_found = true;
    }
    assert(tree_found);
    std::cerr << "placement is valid\n";
}