#include "image.hpp"
#include <iostream>
#include <cassert>

#define DEAD 255
#define ALIVE 0

int count_alive_neighbors(Image const & image, int x, int y)
{
    int count = 0;
    for (int yy = -1; yy <= 1; ++yy)
    {
        for (int xx = -1; xx <= 1; ++xx)
        {
            if (xx != 0 || yy != 0)
            {
                if (image.get_periodic(x+xx, y+yy) == ALIVE)
                {
                    ++count;
                }
            }
        }
    }
    return count;
}

Image conway_step(Image const & image)
{
    Image res(image.width(), image.height());
    for (int y = 0; y < image.height(); ++y)
    {
        for (int x = 0; x < image.width(); ++x)
        {
            int c = count_alive_neighbors(image, x, y);
            if (image(x, y) == ALIVE && (c < 2 || c > 3))
            {
                res(x, y) = DEAD;
            }
            else if (image(x, y) == DEAD && c == 3)
            {
                res(x, y) = ALIVE;
            }
            else
            {
                res(x, y) = image(x, y);
            }
        }
    }
    return res;
}

Image scale_image(Image const & image, int scale)
{
    Image res(scale * image.width(), scale * image.height());
    for (int y = 0; y < res.height(); ++y)
    {
        for (int x = 0; x < res.width(); ++x)
        {
            res(x, y) = image(x/scale, y/scale);
        }
    }
    return res;
}

int main()
{
    {
        Image image = readPGM("conway_init.pgm");

        for (int i = 0; i < 100; ++i)
        {
            image = conway_step(image);
        }

        Image reference = readPGM("conway_test.pgm");
        Image scaled = scale_image(image, 5);
        assert(scaled == reference);

        std::cout << "Test erfolgreich.\n";
    }

    {
        Image image = readPGM("conway_init.pgm");

        for (int i = 0; i < 100; ++i)
        {
            std::string count = "000" + std::to_string(i);
            std::string filename = "conway_sim_" + count.substr(count.size()-3) + ".pgm";
            writePGM(scale_image(image, 5), filename);
            image = conway_step(image);
        }
    }
}

