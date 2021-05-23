#include "../headers/DM_Cache.h"
#include <stdio.h>
#include <fstream>

int main(int argc, char** argv) {

  if (argc < 8) {
    std::cout << "Program Usage: 8 arguments Expected" << std::endl;
    std::cout << "Argument #1: " << std::endl;
    std::cout << "\t Number of Cache Sets" << std::endl;
  }

  std::ifstream input_file("input001.txt");
  std::string input;
  std::string input_instruction;
  std::string input_hex;
  DM_Cache myCache = DM_Cache(256, 1, 16, 13, 13);
  int counter = 0;
  while (input_file >> input) {
    if (counter == 0) {
      input_instruction = input;
    }

    if (counter == 1) {
      input_hex = input;
      int i_hex = std::stoi(input_hex, nullptr, 0);
      if (input_instruction == "s") {
        myCache.store(i_hex);
      } else {
        myCache.load(i_hex);
      }
      //std::cout << input << std::endl;
    }
    counter = (counter + 1) % 3;
  }


  myCache.print_results();

}