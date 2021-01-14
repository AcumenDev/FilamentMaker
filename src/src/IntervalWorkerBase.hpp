#ifndef INTERVAL_WORKER_BASE_HPP
#define INTERVAL_WORKER_BASE_HPP

#include "TimeUtils.hpp"

class IntervalWorkerBase {

  unsigned long _prev_ms = 0;

protected:
  int _interval = 0;

public:
  IntervalWorkerBase(int interval);
  virtual void work(const unsigned long &currentMillis){};
  virtual void update(const unsigned long &currentMillis);

protected:
  bool isWorkTime(const unsigned long &currentMillis);
  bool isWorkTime(const unsigned long &currentMillis, int interval);
};

#endif