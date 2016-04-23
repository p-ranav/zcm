#include <iostream>
#include "test_message.pb.h"
#include "pub_sub_component.hpp"

int main() {
  Pub_Sub_Component * pub_sub_instance = new Pub_Sub_Component();
  std::thread * pub_sub_thread = pub_sub_instance->spawn();
  pub_sub_thread->join();
  return 0;
}
