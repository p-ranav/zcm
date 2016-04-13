/*
 * Client-Server Hello World Test
 * Author: Pranav Srinivas Kumar
 * Date: 2016.04.12
 */

#include <iostream>
#include <string>
#include <thread>
#include <zmq.hpp>

void client_function() {

  zmq::context_t context(1);
  zmq::socket_t socket (context, ZMQ_REQ);
  std::cout << "Connecting to the Hello World Server" << std::endl;

  socket.connect("tcp://localhost:5555");
  while (true) {

    std::string message;
    std::cout << "Enter message: ";
    std::cin >> message;

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
    std::cout << "Received " << reply_string << std::endl;
  }
}


int main() {
  std::thread client_thread(client_function);
  client_thread.join();
  return 0;
}

