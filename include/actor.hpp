/** @file    actor.hpp 
 *  @author  Pranav Srinivas Kumar
 *  @date    2016.04.24
 *  @brief   This file declares the Actor class
 */

#ifndef ACTOR
#define ACTOR
#include "json.hpp"
#include "component.hpp"
#include <dlfcn.h>
#include <fstream>

namespace zcm {

  /**
   * @brief Actor class
   */
  class Actor {
  public:

    /**
     * @brief Configure the component_instances vector
     * @param[in] configuration_file JSON configuration file to parse
     */
    void configure(std::string configuration_file);

    /**
     * @brief Spawn all component instances
     */     
    void run();

    /**
     * @brief Get actor name
     * @return Name of the actor
     */
    std::string get_name();
    
  private:
    std::string name;
    std::vector<Component*> component_instances;
  };

}

#endif
