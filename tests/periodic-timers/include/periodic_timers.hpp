/*
 * Periodic Timers Component
 * Author: Pranav Srinivas Kumar
 * Date: 2016.04.23
 */

#ifndef TIMERS_COMPONENT
#define TIMERS_COMPONENT
#include "component.hpp"

namespace zcm {
  
  class Timers_Component : public Component {
  public:
    Timers_Component();
    void timer_1_function();
    void timer_2_function();
    void timer_3_function();
    void timer_4_function();
    void timer_5_function();
  
  private:
    Timer * timer_1;
    Timer * timer_2;
    Timer * timer_3;
    Timer * timer_4;  
    Timer * timer_5;
  };

}

#endif
