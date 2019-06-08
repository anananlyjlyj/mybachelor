#include "image.hpp"
#include <cassert>

Image chessboard(unsigned int width, unsigned int height, unsigned int square_size)
{
    Image im(width, height);
    for(int k = 0; k < height; k++)
    {
        for (int l = 0; l < width; l++)
        {
            if(((k / square_size) % 2 == 0 && (l / square_size) % 2 == 0) || ((k / square_size) % 2 == 1 && (l / square_size) % 2 == 1))
                im(k, l) = 0;
            else 
                im(k, l) = 1;
        }
    }
    return im;
}

Image invert_image(Image const & image)
{
    Image im(image.width(), image.height());
    for(int k = 0; k < im.height(); k++)
    {
        for (int l = 0; l < im.width(); l++)
        {
            im(k, l) = 255 - image(k, l);
        }
    }
    return im;
}

int main()
{
    Image im(4, 3);
    for(int i = 0; i < im.height(); i++)
    {
        for (int j = 0; j < im.width(); j++)
        {
            assert(im(i, j) == 0);
        }
    }
    assert(to_string(im) == "0 0 0 0\n0 0 0 0\n0 0 0 0\n");
    for(int k = 0; k < im.height(); k++)
    {
        for (int l = 0; l < im.width(); l++)
        {
            im(k, l) = (l * im.width() + k) % 2 ?   0
                                                :   255;
        }
    }
    assert(to_string(im) == "0 255 0 255\n0 255 0 255\n0 25 0 255\n");
    writePGM(im, "board4*3.pgm");
    Image sameim = readPGM("board4*3.pgm");
    assert(to_string(sameim) == "0 255 0 255\n0 255 0 255\n0 25 0 255\n");
    //chessboard
    Image cb = chessboard(4, 3, 1);
    assert(to_string(cb) == "0 255 0 255\n0 255 0 255\n0 25 0 255\n");
    
    Image cb400300 = chessboard(400, 300, 20);
    writePGM(cb400300, "board400*300.pgm");
    Image samecb400300 = readPGM("board400*300.pgm");
    assert(to_string(cb400300) == to_string(samecb400300));
    //inverse
    Image ivcb400300 = invert_image(cb400300);
    writePGM(ivcb400300, "board400*300-inverse.pgm");
    Image ivlena = invert_image(readPGM("lena.pgm"));
    writePGM(ivlena, "lena-inverse.pgm");
    
    return 0;
}