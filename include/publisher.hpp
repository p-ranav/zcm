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
  Publisher(std::string name, std::string endpoint) : 
    name(name),
    endpoint(endpoint) {}

  void publish(std::string message) {
    std::cout << "Sending message... " << message << "; size: " 
	      << message.length() << std::endl;
    zmq::context_t context (1);
    zmq::socket_t publisher (context, ZMQ_PUB);
    publisher.bind(endpoint);
    zmq::message_t message_struct (message.length());
    snprintf ((char *) message_struct.data(), message.length(),
	      "%s", message.c_str());
    publisher.send(message_struct); 
  }

private:
  std::string name;
  std::string endpoint;
};

#endif
