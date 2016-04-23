#include <iostream>
#include "periodic_timers.hpp"

int main() {
  Timers_Component * timers_instance = new Timers_Component();
  std::thread * timers_thread = timers_instance->spawn();

  timers_thread->join();
  return 0;
}
