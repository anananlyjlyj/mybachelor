#include "image.hpp"
#include <iostream>
#include <cassert>

Image mirror_x(Image const & img)
{
    Image res(img.width()*2, img.height());
    for (int y = 0; y < img.height(); ++y)
    {
        for (int x = 0; x < img.width(); ++x)
        {
            res(x, y) = img(x, y);
            res(res.width()-1-x, y) = img(x, y);
        }
    }
    return res;
}

Image mirror_y(Image const & img)
{
    Image res(img.width(), img.height()*2);
    for (int y = 0; y < img.height(); ++y)
    {
        for (int x = 0; x < img.width(); ++x)
        {
            res(x, y) = img(x, y);
            res(x, res.height()-1-y) = img(x, y);
        }
    }
    return res;
}

Image kaleidoscope4(Image const & img)
{
    return mirror_y(mirror_x(img));
}

Image kaleidoscope8(Image const & img)
{
    Image tmp(img.width(), img.height());
    for (int y = 0; y < img.height(); ++y)
    {
        for (int x = 0; x < img.width(); ++x)
        {
            if((img.height() < img.width() && x < y) ||
               (img.height() >= img.width() && x > y))
            {
                tmp(x, y) = img(y, x);
            }
            else
            {
                tmp(x, y) = img(x, y);
            }
        }
    }
    return kaleidoscope4(tmp);
}

int main()
{
    Image lena = readPGM("lena.pgm");

    Image lena_x = mirror_x(lena);
    Image lena_x_test = readPGM("mirror_x_test.pgm");
    assert(lena_x == lena_x_test);

    Image lena_y = mirror_y(lena);
    Image lena_y_test = readPGM("mirror_y_test.pgm");
    assert(lena_y == lena_y_test);

    Image lena_kaleidoskop4 = kaleidoscope4(lena);
    Image lena_kaleidoskop4_test = readPGM("kaleidoskop4_test.pgm");
    assert(lena_kaleidoskop4 == lena_kaleidoskop4_test);

    Image lena_kaleidoskop8 = kaleidoscope8(lena);
    writePGM(lena_kaleidoskop8, "lena_kaleidoskop8.pgm");
    Image lena_kaleidoskop8_test = readPGM("kaleidoskop8_test.pgm");
    assert(lena_kaleidoskop8 == lena_kaleidoskop8_test);

    std::cout << "Alle Tests erfolgreich." << std::endl;
}

