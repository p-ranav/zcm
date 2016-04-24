/*
 * Server Component
 * Author: Pranav Srinivas Kumar
 * Date: 2016.04.23
 */

#ifndef SERVER_COMPONENT
#define SERVER_COMPONENT
#include "component.hpp"

class Server_Component : public Component {
public:
  Server_Component() {
    component_server = new Server("server",
				  60,
				  {"tcp://*:5510"},
				  std::bind(&Server_Component::server_function,
					    this,
					    std::placeholders::_1),
				  operation_queue);
    component_server->start();
  }

  std::string server_function(std::string request) {
    TestMessage received_request_obj;
    received_request_obj.ParseFromString(request);
    std::cout << "Server Operation : Received Request: " 
	      << received_request_obj.message() 
	      << " ID : " << received_request_obj.id() << std::endl;
    return "ACK";
  }  

private:
  Server * component_server;
};

#endif
