/** @file    actor.cpp 
 *  @author  Pranav Srinivas Kumar
 *  @date    2016.04.24
 *  @brief   This file contains definitions for the Actor class
 */

#include "actor.hpp"

namespace zcm {

  // Use configuration file to prepare component instance vector
  void Actor::configure(std::string configuration_file) {
    Json::Value root;
    std::ifstream configuration(configuration_file, std::ifstream::binary);
    configuration >> root;

    for (unsigned int i = 0; i < root["Component Instances"].size(); i++) {
      std::string component_library = root["Component Instances"][i]["Definition"].asString();
      void * handle = dlopen(component_library.c_str(), RTLD_NOW);
      if(handle == NULL)
	std::cerr << dlerror() << std::endl;
      else {
	Component * (*create)();
	create = (Component * (*)())dlsym(handle, "create_component");
	component_instances.push_back((Component*)create());
      }
    }
  }

  void Actor::run() {
    for (auto instance : component_instances) {
      std::thread * instance_thread = instance->spawn();
      instance_thread->detach();
    }
    while(true) {} 
  }

  std::string Actor::get_name() {
    return name;
  }

}
