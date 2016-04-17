#include <iostream>
#include "pub_sub_component.hpp"

int main() {
  Pub_Sub_Component * new_instance = new Pub_Sub_Component("publish_subscribe_component");
  new_instance->init();
  new_instance->run();
  return 0;
}
