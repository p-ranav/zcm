/*
 * Subscriber Component
 * Author: Pranav Srinivas Kumar
 * Date: 2016.04.16
 */

#ifndef SUBSCRIBER_COMPONENT
#define SUBSCRIBER_COMPONENT
#include "component.hpp"
#include "test_message.pb.h"

namespace zcm {

  class Subscriber_Component : public Component {
  public:
    Subscriber_Component();
    void subscriber_function(std::string received_message);
  
  private:
    Subscriber * component_subscriber;
  };

}

#endif
