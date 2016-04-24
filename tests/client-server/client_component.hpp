/*
 * Client Component
 * Author: Pranav Srinivas Kumar
 * Date: 2016.04.23
 */

#ifndef CLIENT_COMPONENT
#define CLIENT_COMPONENT
#include "component.hpp"

namespace zcm {

  class Client_Component : public Component {
  public:
    Client_Component() {
      component_timer = new Timer("timer_1",
				  50,
				  1000000000,				
				  std::bind(&Client_Component::timer_function, this),
				  operation_queue);
      component_timer->start();
      component_client = new Client("client", {"tcp://127.0.0.1:5510"});
    }

    void timer_function() {
      // Create new message
      TestMessage new_message;
      new_message.set_message("client_timer_message");
      new_message.set_id(0);

      // Prepare request string
      std::string * request_string = new std::string;
      new_message.SerializeToString(request_string);

      // Call server
      std::string response = component_client->call(*request_string);
      std::cout << "Client Timer : Received response: " << response << std::endl;
    }
  
  private:
    Timer * component_timer;
    Client * component_client;
  };

}

#endif
