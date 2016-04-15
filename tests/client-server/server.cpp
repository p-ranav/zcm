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
#include "server.hpp"

void server_function() {
  Server my_server("tcp://*:5555");
  my_server.recv();
}

int main() {
  std::thread server_thread(server_function);
  server_thread.join();
  return 0;
}


