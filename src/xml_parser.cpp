/** @file    xml_parser.cpp 
 *  @author  Pranav Srinivas Kumar
 *  @date    2016.04.24
 *  @brief   This file contains definitions for the XML_Parser class
 */

#include "xml_parser.hpp"

namespace zcm {

  // Construct an XML_Parser object
  XML_Parser::XML_Parser(const char * filename) :
    filename(filename) {
    document.LoadFile(filename);
    root = document.FirstChild();
    if (root == nullptr) {
      std::cout << "Error loading XML file!" << std::endl;
    }
  }

  // Parse the configuration XML file
  void XML_Parser::parse() {
    // Find node
    tinyxml2::XMLElement * element = root->FirstChildElement("node");
    if (element == nullptr)
      std::cout << "Error parsing node!" << std::endl;

    // Parse node name
    const char * node = nullptr;
    node = element->Attribute("name");
    if (node == nullptr)
      std::cout << "Error parsing node name!" << std::endl;
    std::string node_name = node;

    std::cout << "node name: " << node_name << std::endl;

    tinyxml2::XMLElement * instance = element->FirstChildElement("component_instance");
    while (instance != nullptr) {
    
      // Find component instance name
      const char * component_instance = nullptr;
      component_instance = instance->Attribute("name");
      if (component_instance == nullptr)
	std::cout << "Error parsing component instance!" << std::endl;
      std::string instance_name = component_instance;
      std::cout << "Component Instance: " << instance_name << std::endl;

      // Goto next component instance
      instance = instance->NextSiblingElement("component_instance");    
    }    
  }  
  
}
