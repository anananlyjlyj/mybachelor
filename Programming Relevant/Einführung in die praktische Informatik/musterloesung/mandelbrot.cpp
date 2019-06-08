#include <iostream>
#include <cmath>
#include <complex>
#include <algorithm>
#include "image_rgb.hpp"

#ifndef M_PI
#    define M_PI     3.14159265358979323846
#endif

template <typename T>
T sq(T x)
{
    return x*x;
}

class FractalView
{
    double x_center_, y_center_, pixel_side_;
    int max_iter_;

  public:

    FractalView(double xc, double yc, double d)
    : x_center_(xc)
    , y_center_(yc)
    , pixel_side_(d)
    , max_iter_(512)
    {}

  private:
    int iterations_until_limit(std::complex<double> const & c) const
    {
        std::complex<double> z(0.0);
        std::complex<double> diff(c);

        for(int i=0; i<max_iter_; ++i)
        {
            if(std::norm(z) >= 1000.0)
                return i;
            z = z*z + c;
        }
        return max_iter_;
    }

    std::complex<double> pixel_to_complex(int w, int h, double ix, double iy) const
    {
        int cx = w / 2,
            cy = h / 2;

        return std::complex<double>((ix - cx) * pixel_side_ + x_center_,
                                    (iy - cy) * pixel_side_ + y_center_);
    }

    uint16_t gray_scheme(int num_iterations) const
    {
        if(num_iterations == max_iter_)
            return 0;
        return uint16_t(255.0*std::pow((double)num_iterations/max_iter_, 0.3333));
    }

    RGBColor color_scheme(int num_iterations) const
    {
        if(num_iterations == max_iter_)
            return RGBColor();
        double n = std::pow(num_iterations,1./5.);
        double m = std::pow(max_iter_,1./5.);
        double H = 180.0 * std::sin(n * 2.0 * M_PI / m + 0.2) + 180.0;
        // double S = 0.4 * std::sin(n * 0.5 * M_PI / 13.0) + 0.5;
        double S = 1.0;
        double V = 0.3 * std::sin(n * 0.5 * M_PI / 200.0) + 0.7;
        return hsv_to_rgb(H, S, V);
    }

    void set_pixel(uint16_t & pixel, int num_iterations) const
    {
        pixel = gray_scheme(num_iterations);
    }

    void set_pixel(RGBColor & pixel, int num_iterations) const
    {
        pixel = color_scheme(num_iterations);
    }

  public:
    template <typename PixelType>
    void render_mandelbrot(Image<PixelType> & img) const
    {
        int w = img.width(),
            h = img.height();

        for(int y=0; y<h; ++y)
        {
            for(int x=0; x<w; ++x)
            {
                int i1 = iterations_until_limit(pixel_to_complex(w, h, x + 0.25, y + 0.25)),
                    i2 = iterations_until_limit(pixel_to_complex(w, h, x - 0.25, y + 0.25)),
                    i3 = iterations_until_limit(pixel_to_complex(w, h, x + 0.25, y - 0.25)),
                    i4 = iterations_until_limit(pixel_to_complex(w, h, x - 0.25, y - 0.25));
                int s = (i1 + i2 + i3 + i4) / 4;

                set_pixel(img(x,y), s);
            }
        }
    }

    void moveUp(int height)
    {
        y_center_ += (height / 4) * pixel_side_;
    }

    void moveDown(int height)
    {
        y_center_ -= (height / 4) * pixel_side_;
    }

    void moveLeft(int width)
    {
        x_center_ -= (width / 4) * pixel_side_;
    }

    void moveRight(int width)
    {
        x_center_ += (width / 4) * pixel_side_;
    }

    void zoomIn()
    {
        pixel_side_ *= 0.5;
    }

    void zoomOut()
    {
        pixel_side_ *= 2.0;
    }
};

int main()
{
    const int w = 640, h = 480;

    // typedef uint16_t PixelType;
    typedef RGBColor PixelType;
    Image<PixelType> img(w, h);

    FractalView f(0.0, 0.0, 0.00625);
    f.render_mandelbrot(img);
    writePNM(img, "mandelbrot_overview");
    writePNM(img, "mandelbrot");

    while(true)
    {
        std::string c;
        std::cout << "Kommando: ";
        std::cin >> c;
        if(c == "b")
            break;
        else if(c == "s")
            f.moveUp(h);
        else if(c == "w")
            f.moveDown(h);
        else if(c == "d")
            f.moveLeft(w);
        else if(c == "a")
            f.moveRight(w);
        else if(c == "+")
            f.zoomIn();
        else if(c == "-")
            f.zoomOut();

        f.render_mandelbrot(img);
        writePNM(img, "mandelbrot");
    }
}
