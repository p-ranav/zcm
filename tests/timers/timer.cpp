/*
 * Simple Timer Example
 * Author: Pranav Srinivas Kumar
 * Date: 2016.04.12
 */

#include <iostream>
#include <chrono>
#include <ratio>
#include <thread>
#include <mutex>

std::mutex cout_mutex;

// Timer Thread Function
void timer_function(std::string timer_name, std::chrono::duration<long long, std::ratio<1, 1000000000>> timer_period) {
  cout_mutex.lock();
  std::cout << timer_name << "::Period=" << timer_period.count() << std::endl;
  cout_mutex.unlock();
  while(true) {
    auto start = std::chrono::high_resolution_clock::now();
    while(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start) < timer_period) {}
    auto expiry = std::chrono::high_resolution_clock::now();    
    cout_mutex.lock();
    std::cout << timer_name << "::Timer Expired::Period::" <<
      std::chrono::duration_cast<std::chrono::nanoseconds>(expiry - start).count() << " ns" << std::endl;
    cout_mutex.unlock();
  }
}


int main() {

  // Timer 1
  std::chrono::duration<long long, std::ratio<1, 1000000000>> timer_period_1(1000000000);
  std::thread timer_thread_1(timer_function, "Timer_1", timer_period_1);

  // Timer 2
  std::chrono::duration<long long, std::ratio<1, 1000000000>> timer_period_2(500000000);
  std::thread timer_thread_2(timer_function, "Timer_2", timer_period_2);  

  // Timer 3
  std::chrono::duration<long long, std::ratio<1, 1000000000>> timer_period_3(2000000000);
  std::thread timer_thread_3(timer_function, "Timer_3", timer_period_3);    

  timer_thread_1.join();
  timer_thread_2.join();
  timer_thread_3.join();
  return 0;
}
