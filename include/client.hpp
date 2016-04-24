/** @file    client.hpp 
 *  @author  Pranav Srinivas Kumar
 *  @date    2016.04.24
 *  @brief   This file declares the Client class
 */

#ifndef CLIENT
#define CLIENT
#include <iostream>
#include <zmq.hpp>

/**
 * @brief Client class
 */
class Client {
public:

  /**
   * @brief Construct a client object
   * @param[in] name Client name
   */   
  Client(std::string name);

  /**
   * @brief Construct a client object with known endpoints
   * @param[in] name Client name
   * @param[in] endpoints A vector of endpoint strings
   */   
  Client(std::string name, std::vector<std::string> endpoints);

  /**
   * @brief Close the client ZMQ socket and destroy the context
   */    
  ~Client();

  /**
   * @brief Connect the client to a new set of endpoints
   * @param[in] new_endpoints New set of endpoints as a vector
   */ 
  void connect(std::vector<std::string> new_endpoints);

  /**
   * @brief Return the client name
   * @return Client name
   */    
  std::string get_name();

  /**
   * @brief Call the server
   * @param[in] message The message string. Serialize complex objects to strings with protobuf
   */  
  std::string call(std::string message);
  
private:

  /** @brief Name of the publisher */  
  std::string name;

  /** @brief Vector of endpoints to connect to */  
  std::vector<std::string> endpoints;

  /** @brief ZMQ Context of the client */  
  zmq::context_t * context;

  /** @brief ZMQ Socket of the client */  
  zmq::socket_t * client_socket;
};

#endif
