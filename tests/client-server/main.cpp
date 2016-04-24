#include <iostream>
#include "test_message.pb.h"
#include "client_component.hpp"
#include "server_component.hpp"

int main() {
  zcm::Client_Component * client_instance = new zcm::Client_Component();
  std::thread * client_thread = client_instance->spawn();

  zcm::Server_Component * server_instance = new zcm::Server_Component();
  std::thread * server_thread = server_instance->spawn();      

  client_thread->join();
  server_thread->join();
  return 0;
}
