#include "image.hpp"
#include <cassert>
#include <iostream>

Image
chessboard(unsigned int width, unsigned int height, unsigned int square_size)
{
    Image res(width, height);
    for(int y=0; y<height; ++y)
    {
        for(int x=0; x<width; ++x)
        {
            int xx = x / square_size;
            int yy = y / square_size;
            if((xx+yy) % 2 != 0)
                res(x,y) = 255;
        }
    }
    return res;
}

Image
invert_image(Image const & image)
{
    Image res(image.width(), image.height());
    for(int y=0; y<image.height(); ++y)
    {
        for(int x=0; x<image.width(); ++x)
        {
            res(x,y) = 255 - image(x,y);
        }
    }
    return res;
}

int main()
{
  try {
    Image image(4,3);
    assert(image.width() == 4);
    assert(image.height() == 3);
    for(int y=0; y<image.height(); ++y)
    {
        for(int x=0; x<image.width(); ++x)
        {
            assert(image(x,y) == 0);
        }
    }

    assert(to_string(image) == "0 0 0 0\n0 0 0 0\n0 0 0 0\n");

    for(int y=0; y<image.height(); ++y)
    {
        for(int x=0; x<image.width(); ++x)
        {
            if((x+y) % 2 != 0)
                image(x,y) = 255;
        }
    }


    assert(to_string(image) == "0 255 0 255\n255 0 255 0\n0 255 0 255\n");

    writePGM(image, "board4x3.pgm");

    Image board = readPGM("board4x3.pgm");
    assert(image.width() == board.width());
    assert(image.height() == board.height());
    assert(image == board);

    Image board_large = chessboard(400, 300, 20);
    writePGM(board_large, "board400x300.pgm");

    Image board_res = readPGM("board400x300.pgm");
    assert(board_large.width() == board_res.width());
    assert(board_large.height() == board_res.height());
    assert(board_large == board_res);

    writePGM(invert_image(board_large), "board400x300-inverse.pgm");

    Image lena = readPGM("lena.pgm");
    writePGM(invert_image(lena), "lena-inverse.pgm");
  }
  catch(std::exception & e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}