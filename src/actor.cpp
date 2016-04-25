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
	Component * component_instance = (Component*)create();

	std::map<std::string, std::vector<std::string>> publishers_config_map;
	std::map<std::string, std::vector<std::string>> subscribers_config_map;
	std::map<std::string, std::vector<std::string>> clients_config_map;
	std::map<std::string, std::vector<std::string>> servers_config_map;	

	// Configure all component instance publishers
	for (unsigned int j = 0; j < root["Component Instances"][i]["Publishers"].size(); j++) {
	  Json::Value publisher_config = root["Component Instances"][i]["Publishers"][j];
	  std::string publisher_name = publisher_config["Name"].asString();
	  for (unsigned int k = 0; k < publisher_config["Endpoints"].size(); k++) {
	    publishers_config_map[publisher_name].push_back(publisher_config["Endpoints"][k].asString());
	  }
	}

	// Configure all component instance subscribers
	for (unsigned int j = 0; j < root["Component Instances"][i]["Subscribers"].size(); j++) {
	  Json::Value subscriber_config = root["Component Instances"][i]["Subscribers"][j];
	  std::string subscriber_name = subscriber_config["Name"].asString();
	  for (unsigned int k = 0; k < subscriber_config["Endpoints"].size(); k++) {
	    subscribers_config_map[subscriber_name].push_back(subscriber_config["Endpoints"][k].asString());
	  }
	}

	// Configure all component instance clients
	for (unsigned int j = 0; j < root["Component Instances"][i]["Clients"].size(); j++) {
	  Json::Value client_config = root["Component Instances"][i]["Clients"][j];
	  std::string client_name = client_config["Name"].asString();
	  for (unsigned int k = 0; k < client_config["Endpoints"].size(); k++) {
	    clients_config_map[client_name].push_back(client_config["Endpoints"][k].asString());
	  }
	}

	// Configure all component instance servers
	for (unsigned int j = 0; j < root["Component Instances"][i]["Servers"].size(); j++) {
	  Json::Value server_config = root["Component Instances"][i]["Servers"][j];
	  std::string server_name = server_config["Name"].asString();
	  for (unsigned int k = 0; k < server_config["Endpoints"].size(); k++) {
	    servers_config_map[server_name].push_back(server_config["Endpoints"][k].asString());
	  }
	}	
	
	component_instance->configure_publishers(publishers_config_map);
	component_instance->configure_subscribers(subscribers_config_map);
	component_instance->configure_clients(clients_config_map);
	component_instance->configure_servers(servers_config_map);
	component_instances.push_back(component_instance);
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
