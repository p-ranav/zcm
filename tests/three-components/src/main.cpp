#include <iostream>
#include <dlfcn.h>
#include "actor.hpp"
#include "component_1.hpp"
#include "component_2.hpp"
#include "component_3.hpp"

int main() {

  zcm::Actor three_component_actor;
  three_component_actor.configure("configuration.json");
  three_component_actor.run();
  
  return 0;
}
