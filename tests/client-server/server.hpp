/*
 * Server class
 * Author: Pranav Srinivas Kumar
 * Date: 2016.04.15
 */

#ifndef SERVER
#define SERVER

#include <iostream>
#include <string>
#include <zmq.hpp>

class Server {
public:
  Server(std::string endpoint) : endpoint(endpoint) {}

  void recv() {
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REP);
    socket.bind (endpoint);

    while (true) {
      zmq::message_t request;

      // Wait for a client request
      socket.recv (&request);
      std::string request_string = std::string(static_cast<char *>(request.data()), 
					       request.size());
      std::cout << "Received " << request_string << std::endl;

      // Prepare and send response back
      std::string response("ACK");
      zmq::message_t reply (response.length());
      memcpy (reply.data (), response.c_str(), response.length());
      socket.send (reply);
    }    
  }

private:
  std::string endpoint;
};

#endif
