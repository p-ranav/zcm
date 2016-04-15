/*
 * Client Class
 * Author: Pranav Srinivas Kumar
 * Date: 2016.04.15
 */

#ifndef CLIENT
#define CLIENT

#include <iostream>
#include <zmq.hpp>

class Client {
public:
  Client(std::string endpoint) : endpoint(endpoint) {}

  std::string call(std::string message) {    
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REQ);
    socket.connect(endpoint);

    // Prepare request message
    zmq::message_t request (message.length());
    memcpy(request.data(), message.c_str(), message.length());
    std::cout << "Sending " << message << std::endl;
    socket.send(request);

    // Receive response from server
    zmq::message_t reply;
    socket.recv(&reply);
    std::string reply_string = std::string(static_cast<char *>(reply.data()), 
					   reply.size());
    return reply_string;
  }

private:
  std::string endpoint;
};
#endif
