/*
 * Client-Server Hello World Test
 * Author: Pranav Srinivas Kumar
 * Date: 2016.04.12
 */

#include <iostream>
#include <string>
#include <thread>
#include <unistd.h>
#include <zmq.hpp>

void server_function() {
  zmq::context_t context (1);
  zmq::socket_t socket (context, ZMQ_REP);
  socket.bind ("tcp://*:5555");

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

int main() {
  std::thread server_thread(server_function);
  server_thread.join();
  return 0;
}


