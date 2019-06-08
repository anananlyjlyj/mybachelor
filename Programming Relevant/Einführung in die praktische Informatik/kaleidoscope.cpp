#include <cassert>
#include "image.hpp"

Image mirror_x(Image const & image)
{
    Image im(image.width() * 2, image.height());
    for(int k = 0; k < im.height(); k++)
    {
        for (int l = 0; l < im.width(); l++)
        {
            if(l <= image.width())
                im(k, l) = image(k, l);
            else
                im(k, l) = image(k, 2 * image.width() - l);
        }
    }
    return im;
    
}
Image mirror_y(Image const & image)
{
    Image im(image.width(), image.height() * 2);
    for(int k = 0; k < im.height(); k++)
    {
        for (int l = 0; l < im.width(); l++)
        {
            if(k <= image.height())
                im(k, l) = image(k, l);
            else
                im(k, l) = image(2 * image.height() - k, l);
        }
    }
    return im;
    
}
Image kaleidoscope4(Image const & image)
{
    Image im = mirror_y(mirror_x(image));
    return im;
}

Image kaleidoscope8(Image const & image)
{
    Image im(image.width(), image.height());
    for(int k = 0; k < im.height(); k++)
    {
        for (int l = 0; l < im.width(); l++)
        {
            if(k >= l)
                im(k, l) = image(k, l);
            else
                im(k, l) = image(l, k);
        }
    }
    Image ima = mirror_y(mirror_x(im));
    return ima;
    
}

int main ()
{
    Image lena = readPGM("lena.pgm");
    Image lenax = mirror_x(lena);
    assert(lenax == readPGM("mirror_x_test.pgm"));
    Image lenay = mirror_y(lena);
    assert(lenay == readPGM("mirror_y_test.pgm"));
    Image lena4 = kaleidoscope4(lena);
    assert(lena4 == readPGM("kaleidoscope4_test.pgm"));
    Image lena8 = kaleidoscope8(lena);
    assert(lena8 == readPGM("kaleidoscope8_test.pgm"));
    return 0;
}