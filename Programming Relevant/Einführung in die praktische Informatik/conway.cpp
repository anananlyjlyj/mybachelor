#include "image.hpp"
#include <iostream>
#include <cassert>

int count_alive_neighbors(Image const & image, int x, int y)
{
    int count = 0;
    for(int i = 0; i < 3; i++)
    {
        if(image.get_periodic(x - 1, y - 1 + i) == 0)
            count++;
        if(image.get_periodic(x + 1, y - 1 + i) == 0)
            count++;
    }
    if(image.get_periodic(x, y - 1) == 0)
        count++;
    if(image.get_periodic(x, y + 1) == 0)
        count++;
    return count;
}
Image conway_step(Image const & image)
{
    Image res = image;
    for(int i = 0; i < image.height(); i++)
    {
        for(int j = 0; j < image.width(); j++)
        {
            int count = count_alive_neighbors(image, i, j);
            if((image(i,j) == 0 && count == 2) || count == 3)
            {
                res(i, j) = 0;
            }
            else
                res(i, j) = 255;
        }
    }
    return res;
}
Image scale_image(Image const & image, int scale)
{
    Image res(image.width() * scale, image.height() * scale);
    for(int i = 0; i < res.height(); i++)
    {
        for(int j = 0; j < res.width(); j++)
        {
            res(i, j) = image(i / scale, j / scale);
        }
    }
    return res;
}

int main()
{
    Image im = readPGM("conway_init.pgm");
    Image res = im;
    for(int i = 0; i < 100; i++)
    {
        res = conway_step(res);
    }
    res = scale_image(res, 5);
    assert(res == readPGM("conway_test.pgm"));
    Image res2 = im;
    return 0;
}