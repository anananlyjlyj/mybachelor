#include "image.hpp"
#include <cassert>
#include <iostream>
#include <cmath>

double sq(double x)
{
    return x*x;
}

int main()
{
    const int w = 640, h = 480;

    Image img1(w, h);

    int cx = w / 2,
        cy = h / 2;

    double xc = 0.0, yc = 0.0;
    double d1 = 1.0 / 64.0;

    for(int y=0; y<h; ++y)
    {
        for(int x=0; x<w; ++x)
        {
            double xx = (x - cx) * d1 + xc;
            double yy = (y - cy) * d1 + yc;
            img1(x, y) = uint16_t(255.0 * sq(std::sin(sq(xx) + sq(yy))));
        }
    }

    writePGM(img1, "image1.pgm");

    Image img2(w, h);

    double d2 = 1.0;

    for(int y=0; y<img1.height(); ++y)
    {
        for(int x=0; x<img1.width(); ++x)
        {
            double xx = (x - cx) * d2 + xc;
            double yy = (y - cy) * d2 + yc;
            img2(x, y) = uint16_t(255.0 * sq(std::sin((sq(xx) + sq(yy))/4096.0)));
        }
    }

    assert(img1 == img2);

    writePGM(img2, "image2.pgm");
}