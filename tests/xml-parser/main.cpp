#include <iostream>
#include "xml_parser.hpp"

int main() {

  XML_Parser parser("configuration.xml");
  parser.parse();
}
