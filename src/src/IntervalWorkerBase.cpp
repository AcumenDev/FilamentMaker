#include "IntervalWorkerBase.hpp"

IntervalWorkerBase::IntervalWorkerBase(int interval) {
  this->_interval = interval;
}

bool IntervalWorkerBase::isWorkTime(const unsigned long &currentMillis) {
  return TimeUtils::isWorkTime(_prev_ms, currentMillis, _interval);
}

bool IntervalWorkerBase::isWorkTime(const unsigned long &currentMillis,
                                    int interval) {
  return TimeUtils::isWorkTime(_prev_ms, currentMillis, interval);
}

void IntervalWorkerBase::update(const unsigned long &currentMillis) {
  if (isWorkTime(currentMillis)) {
    work(currentMillis);
    _prev_ms = currentMillis;
  }
}