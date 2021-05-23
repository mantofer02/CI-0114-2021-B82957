#include "../headers/DM_Cache.h"
#include <stdio.h>
#include <fstream>

int main(void) {

  std::ifstream input_file("input001.txt");
  
  std::string input;
  while (input_file >> input) {
    std::cout << input << std::endl;
  }


  DM_Cache myCache = DM_Cache(1, 16, 4, 13, 13);
  
  std::string hex = "0xFF";
  int i_hex = std::stoi(hex, nullptr, 0);
  std :: cout << "HOLA" << std :: endl;
  std :: cout << i_hex << std :: endl;

  size_t blockAssign = myCache.get_block_address(17);
  size_t tag_value = myCache.get_tag_value(17);
  std :: cout << blockAssign << std :: endl;
  std :: cout << tag_value << std :: endl;
}