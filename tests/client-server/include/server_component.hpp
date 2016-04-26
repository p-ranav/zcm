/*
 * Server Component
 * Author: Pranav Srinivas Kumar
 * Date: 2016.04.23
 */

#ifndef SERVER_COMPONENT
#define SERVER_COMPONENT
#include "component.hpp"
#include "test_message.pb.h"

namespace zcm {

  class Server_Component : public Component {
  public:
    Server_Component();
    std::string server_function(std::string request);

  private:
    Server * component_server;
  };

}

#endif
