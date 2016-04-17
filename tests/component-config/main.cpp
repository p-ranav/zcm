#include <iostream>
#include "pub_sub_component.hpp"

int main() {
  Pub_Sub_Component * new_instance = new Pub_Sub_Component();
  new_instance->init();

  Publisher * pub_ptr = new_instance->get_publisher("timer_pub_1");
  if (pub_ptr)
    std::cout << "Retrieved publisher : " << pub_ptr->get_name() << std::endl;

  Subscriber * sub_ptr = new_instance->get_subscriber("subscriber_operation");
  if (sub_ptr)
    std::cout << "Retrieved subscriber : " << sub_ptr->get_name() << std::endl;

  Timer * timer_ptr = new_instance->get_timer("timer_1");
  if (timer_ptr)
    std::cout << "Retrieved timer : " << timer_ptr->get_name() << std::endl;

  std::thread * instance_1_thread = new_instance->spawn();
  instance_1_thread->join();
  return 0;
}
