
#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>
#include <ctime>


  
class timer
{
public:
  timer()
  : _is_running{false}
  {}

  inline
  bool is_running() const 
  {return _is_running;}

  void start()
  {
    _is_running = true;
    _start = std::chrono::high_resolution_clock::now();
  }

  double stop()
  {
    if(!_is_running)
      return 0.0;

    _stop = std::chrono::high_resolution_clock::now();
    _is_running = false;

    auto ticks = std::chrono::duration_cast<std::chrono::nanoseconds>(_stop - _start).count();
    return static_cast<double>(ticks) * 1.e-9;
  }

private:
  using time_point_type = 
    std::chrono::time_point<std::chrono::high_resolution_clock>;
  time_point_type _start;
  time_point_type _stop;

  bool _is_running;
};

class cumulative_timer
{
public:
  cumulative_timer()
  {
    reset();
  }

  void reset()
  {
    _num_runs = 0;
    _total_runtime = 0.0;
  }

  double get_average_runtime() const
  {
    if(_num_runs == 0)
      return 0.0;

    return _total_runtime / static_cast<double>(_num_runs);
  }

  double get_total_runtime() const
  {
    return _total_runtime;
  }

  unsigned get_num_runs() const
  {
    return _num_runs;
  }

  void start()
  {
    _timer.start();
  }

  void stop()
  {
    _total_runtime += _timer.stop();
    _num_runs++;
  }

private:
  double _total_runtime;
  unsigned _num_runs;
  timer _timer;
};


#endif
