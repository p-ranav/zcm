#include <iostream>
#include <dlfcn.h>
#include "component_1.hpp"
#include "component_2.hpp"
#include "component_3.hpp"

zcm::Component * load_component(const char * component_library) {
  void* handle = dlopen(component_library, RTLD_NOW);
  if(handle == NULL) {
    std::cerr << dlerror() << std::endl;
    exit(-1);
  }
  zcm::Component* (*create)();
  create = (zcm::Component* (*)())dlsym(handle, "create_component");
  return (zcm::Component*)create();
}

int main() {

  zcm::Component * component_1 = load_component("./component_1.so");
  std::thread * component_1_thread = component_1->spawn();
  zcm::Component * component_2 = load_component("./component_2.so");
  std::thread * component_2_thread = component_2->spawn();
  zcm::Component * component_3 = load_component("./component_3.so");
  std::thread * component_3_thread = component_3->spawn();
 
  component_1_thread->join();
  component_2_thread->join();
  component_3_thread->join();  
  
  return 0;
}
