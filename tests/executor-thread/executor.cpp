/*
 * Component Executor Thread
 * Author: Pranav Srinivas Kumar
 * Date: 2016.04.13
 */

#include <iostream>
#include <string>
#include <chrono>
#include <ratio>
#include <thread>
#include <mutex>
#include <vector>

std::mutex cout_mutex;

class Timer {
public:

  Timer(std::string name, long long period) : 
    name(name), 
    period(std::chrono::nanoseconds(period)) {}

  void operation() {
    while(true) {
      auto start = std::chrono::high_resolution_clock::now();
      while(std::chrono::duration_cast<std::chrono::nanoseconds>
      (std::chrono::high_resolution_clock::now() - start) < period) {}
      auto expiry = std::chrono::high_resolution_clock::now();
    cout_mutex.lock();
    std::cout << name << "::Timer Expired::Period::" <<
      std::chrono::duration_cast<std::chrono::nanoseconds>(expiry - start).count() 
	      << " ns" << std::endl;
    cout_mutex.unlock();      
    }    
  }

  std::thread spawn() {
    return std::thread(&Timer::operation, this);
  }

private:
  std::string name;
  std::chrono::duration<long long, std::ratio<1, 1000000000>> period;
};

int main() {

  Timer new_timer("Timer_1", 1000000000);  
  new_timer.spawn().join();

  return 0;
}
