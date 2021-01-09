#ifndef INTERVAL_WORKER_BASE_HPP
#define INTERVAL_WORKER_BASE_HPP

#include "TimeUtils.hpp"

class IntervalWorkerBase {

  unsigned long _prev_ms = 0;
  int _interval = 0;

public:
  IntervalWorkerBase(int interval);
  virtual void work( unsigned long currentMillis){};
  virtual void update( unsigned long currentMillis);

protected:
  bool isWorkTime(unsigned long currentMillis);
  bool isWorkTime(unsigned long currentMillis, int interval);
};

#endif 