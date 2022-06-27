#ifndef TemperatureValue_hpp
#define TemperatureValue_hpp

class TemperatureValueHolder {
private:
  double value = 0;

public:
  TemperatureValueHolder(/* args */);
  ~TemperatureValueHolder();
  void set(double &value);
  double *get();
};

TemperatureValueHolder::TemperatureValueHolder(/* args */) {}

TemperatureValueHolder::~TemperatureValueHolder() {}

void TemperatureValueHolder::set(double &value) { this->value = value; }
double *TemperatureValueHolder::get() { return &value; }
#endif