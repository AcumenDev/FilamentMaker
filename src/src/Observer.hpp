#ifndef Observer_HPP
#define Observer_HPP

class Observer {
private:
  /* data */
public:
  Observer(/* args */){};
  virtual ~Observer(){};
  virtual void event(int index, int value) = 0;
};

#endif