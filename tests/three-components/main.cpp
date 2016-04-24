#include <iostream>
#include "component_1.hpp"
#include "component_2.hpp"
#include "component_3.hpp"

int main() {
  Component_1 * instance_1 = new Component_1();
  std::thread * instance_1_thread = instance_1->spawn();

  Component_2 * instance_2 = new Component_2();
  std::thread * instance_2_thread = instance_2->spawn();

  Component_3 * instance_3 = new Component_3();
  std::thread * instance_3_thread = instance_3->spawn();

  instance_1_thread->join();
  instance_2_thread->join();
  instance_3_thread->join();
  return 0;
}
