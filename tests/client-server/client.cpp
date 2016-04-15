/*
 * Client-Server Hello World Test
 * Author: Pranav Srinivas Kumar
 * Date: 2016.04.12
 */

#include <iostream>
#include <string>
#include <thread>
#include <zmq.hpp>
#include "client.hpp"

void client_function() {
  while(true) {
    Client new_client("tcp://localhost:5555");
    std::string message;
    std::cout << "New Message: ";
    std::cin >> message;
    std::string reply = new_client.call(message);
    std::cout << "Received: " << reply << std::endl;
  }
}


int main() {
  std::thread client_thread(client_function);
  client_thread.join();
  return 0;
}

