/*
 * Client Component
 * Author: Pranav Srinivas Kumar
 * Date: 2016.04.25
 */

#include "client_component.hpp"

namespace zcm {

  extern "C" {
    Component* create_component() {
      return new Client_Component();
    }
  }  

  Client_Component::Client_Component() {
    component_timer = new Timer("timer_1",
				50,
				1000000000,				
				std::bind(&Client_Component::timer_function, this),
				operation_queue);
    component_client = new Client("client");
    add_timer(component_timer);
    add_client(component_client);
  }

  void Client_Component::timer_function() {
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

}
