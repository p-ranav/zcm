#include <iostream>
#include "pub_sub_component.hpp"
#include <unistd.h>

int main() {
  Pub_Sub_Component * new_instance = new Pub_Sub_Component();
  new_instance->init();
  std::thread * instance_1_thread = new_instance->spawn();
  instance_1_thread->join();
  return 0;
}
