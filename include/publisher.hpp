/*
 * Publisher class
 * Author: Pranav Srinivas Kumar
 * Date: 2016.04.16
 */

#ifndef PUBLISHER
#define PUBLISHER
#include <zmq.hpp>

class Publisher {
public:
  Publisher(std::string name, std::vector<std::string> endpoints) : 
    name(name),
    endpoints(endpoints) {
    context = new zmq::context_t(1);
    publisher_socket = new zmq::socket_t(*context, ZMQ_PUB);
    for (auto endpoint : endpoints) {
      try {
	publisher_socket->bind(endpoint);
      } catch (zmq::error_t error) {
	std::cout << "Unable to bind publisher " << 
	  name << " to " << endpoint << std::endl;      
      }
    }
  }

  ~Publisher() {
    publisher_socket->close();
    delete context;
    delete publisher_socket;
  }

  std::string get_name() {
    return name;
  }

  void add_connection(std::string new_connection) {
    try {
    publisher_socket->bind(new_connection);
    } catch (zmq::error_t error) {
      std::cout << "ERROR::add_connection failed trying to bind to address: " 
		<< new_connection << std::endl;
    }
  }

  void send(std::string message) {
    zmq::message_t message_struct (message.length());
    memcpy(message_struct.data(), message.c_str(), message.length());
    publisher_socket->send(message_struct); 
  }

private:
  std::string name;
  zmq::context_t * context;
  zmq::socket_t * publisher_socket;
  std::vector<std::string> endpoints;
};

#endif
