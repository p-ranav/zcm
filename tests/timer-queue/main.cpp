#include<iostream>
#include "timer.hpp"
int main()
{
    Timer t;
    // Timer fires once, one second from now
    t.create(1000, 0,
             []() {
                 std::cout << "Non-periodic timer fired" << std::endl;
             });
    // Timer fires every second, starting five seconds from now
    t.create(5000, 1000,
             []() {
                 std::cout << "Timer fired 0" << std::endl;
             });
    // Timer fires every second, starting now
    t.create(0, 1000,
             []() {
                 std::cout << "Timer fired 1" << std::endl;
             });
    // Timer fires every 100ms, starting now
    t.create(0, 100,
             []() {
                 std::cout << "Timer fired 2" << std::endl;
             });
}
