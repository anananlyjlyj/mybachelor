#inlcude <complex>

class FaractalView
{
    double x_center_;
    double y_center_;
    double pixel_side_;
    int iterations_until_limit(std::complex<double> const & c) const
    {
        int limit = 1000;
        std::complex<double> res;
        for(int i = 0; res < limit && i < 512; i++)
        {
            res += c;
            res = std::norm(res);
        }
        return i;
    }
    std::complex<double> pixel_to_complex(Image const & img, int ix, int iy) const
    {
        
    }
    unit16_t color_scheme(int num_interations) const
    {
        unit16_t x;
    }
public:
    FaractalView ()
    :x_center_(0.0)
    ,y_center_(0.0)
    ,pixel_side_(0.0)
    {}
    void render_mandelbrot(Image & img) const
    {
        
    }
    
};

int main()
{
    return 0;
}