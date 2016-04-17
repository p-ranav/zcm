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
    endpoint(endpoint) {
    context = new zmq::context_t(1);
    publisher_socket = new zmq::socket_t(*context, ZMQ_PUB);
    publisher_socket->bind(endpoint);
  }

  ~Publisher() {
    publisher_socket->close();
    delete context;
    delete publisher_socket;
  }

  void send(std::string message) {
    zmq::message_t message_struct (message.length());
    snprintf ((char *) message_struct.data(), message.length(), "%s", message.c_str());
    publisher_socket->send(message_struct); 
  }

private:
  std::string name;
  zmq::context_t * context;
  zmq::socket_t * publisher_socket;
  std::string endpoint;
};

#endif
