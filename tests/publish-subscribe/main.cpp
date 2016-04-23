#include <iostream>
#include "test_message.pb.h"
#include "publisher_component.hpp"
#include "subscriber_component.hpp"
#include "stdout_redirection.hpp"

int main() {
  redirect_stdout("publish_subscribe.log");
  Publisher_Component * publisher_instance = new Publisher_Component();
  std::thread * publisher_thread = publisher_instance->spawn();

  Subscriber_Component * subscriber_instance = new Subscriber_Component();
  std::thread * subscriber_thread = subscriber_instance->spawn();
  
  publisher_thread->join();
  subscriber_thread->join();
  restore_stdout();
  return 0;
}
