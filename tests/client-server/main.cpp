#include <iostream>
#include "test_message.pb.h"
#include "client_component.hpp"
#include "server_component.hpp"

int main() {
  Client_Component * client_instance = new Client_Component();
  std::thread * client_thread = client_instance->spawn();

  Server_Component * server_instance = new Server_Component();
  std::thread * server_thread = server_instance->spawn();      

  client_thread->join();
  server_thread->join();
  return 0;
}
