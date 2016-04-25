/*
 * Component 2
 * Author: Pranav Srinivas Kumar
 * Date: 2016.04.23
 */

#ifndef COMPONENT_2
#define COMPONENT_2
#include <boost/random/linear_congruential.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/generator_iterator.hpp>
#include <boost/random/mersenne_twister.hpp>
#include "component.hpp"

namespace zcm {

  class Component_2 : public Component {
  public:

    Component_2();
    void timer_function();
    std::string server_function(std::string request);

  private:
    Timer * timer;
    Publisher * publisher;
    Server * server;
  };

}

#endif
