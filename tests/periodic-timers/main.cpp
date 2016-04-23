#include <iostream>
#include "periodic_timers.hpp"
#include "stdout_redirection.hpp"

int main() {
  redirect_stdout("periodic_timers.log");
  Timers_Component * timers_instance = new Timers_Component();
  std::thread * timers_thread = timers_instance->spawn();

  timers_thread->join();
  restore_stdout();
  return 0;
}
