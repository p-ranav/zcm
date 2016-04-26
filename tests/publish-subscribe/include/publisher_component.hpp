/*
 * Publisher Component
 * Author: Pranav Srinivas Kumar
 * Date: 2016.04.25
 */

#ifndef PUBLISHER_COMPONENT
#define PUBLISHER_COMPONENT
#include "component.hpp"
#include "test_message.pb.h"

namespace zcm {

  class Publisher_Component : public Component {
  public:
    Publisher_Component();
    void timer_1_function();

  private:
    Timer * component_timer;
    Publisher * component_publisher;
  };

}

#endif
