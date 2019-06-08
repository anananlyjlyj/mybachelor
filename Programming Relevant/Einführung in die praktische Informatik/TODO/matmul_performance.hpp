#ifndef MATMUL_PERFORMANCE
#define MATMUL_PERFORMANCE

#include "timer.hpp"

/// Measures the GFlops of the multiplication of two NxN matrices
class matrix_multiplication_timer : public cumulative_timer
{
public:
  matrix_multiplication_timer(std::size_t N)
    : _n{N}
  {}

  double get_gflops() const
  {
    double time = this->get_average_runtime();
    // For each matrix element, we need to compute
    // the dot product between two vectors of length N.
    // This dot product consists of N multiplications and
    // N-1 additions.
    std::size_t num_ops = _n * _n * (2 * _n - 1);

    return static_cast<double>(num_ops) / time * 1.e-9;
  }

private:
  std::size_t _n;
};

#endif
