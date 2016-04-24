#include <iostream>
#include "test_message.pb.h"
#include "publisher_component.hpp"
#include "subscriber_component.hpp"

int main() {
  zcm::Publisher_Component * publisher_instance = new zcm::Publisher_Component();
  std::thread * publisher_thread = publisher_instance->spawn();

  zcm::Subscriber_Component * subscriber_instance = new zcm::Subscriber_Component();
  std::thread * subscriber_thread = subscriber_instance->spawn();
  
  publisher_thread->join();
  subscriber_thread->join();
  return 0;
}
