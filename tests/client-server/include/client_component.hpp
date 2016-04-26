/*
 * Client Component
 * Author: Pranav Srinivas Kumar
 * Date: 2016.04.23
 */

#ifndef CLIENT_COMPONENT
#define CLIENT_COMPONENT
#include "component.hpp"
#include "test_message.pb.h"

namespace zcm {

  class Client_Component : public Component {
  public:
    Client_Component();    
    void timer_function();
  
  private:
    Timer * component_timer;
    Client * component_client;
  };

}

#endif
