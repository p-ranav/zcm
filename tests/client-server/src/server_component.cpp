/*
 * Server Component
 * Author: Pranav Srinivas Kumar
 * Date: 2016.04.25
 */

#include "server_component.hpp"

namespace zcm {

  extern "C" {
    Component* create_component() {
      return new Server_Component();
    }
  }    

  Server_Component::Server_Component() {
    component_server = new Server("server",
				  60,
				  std::bind(&Server_Component::server_function,
					    this,
					    std::placeholders::_1),
				  operation_queue);
    add_server(component_server);
  }

  std::string Server_Component::server_function(std::string request) {
    TestMessage received_request_obj;
    received_request_obj.ParseFromString(request);
    std::cout << "Server Operation : Received Request: " 
	      << received_request_obj.message() 
	      << " ID : " << received_request_obj.id() << std::endl;
    return "ACK";
  }  

}

