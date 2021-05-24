#include "../headers/DM_Cache.h"
#include <stdio.h>
#include <fstream>

#define MEMORY_ACCESS 230 
#define CACHE_ACCESS 13

int main(int argc, char** argv) {

  if (argc < 8) {
    std::cout << "Program Usage: 8 arguments Expected" << std::endl;
    std::cout << "Argument #1: " << std::endl;
    std::cout << "\tNumber of Cache Sets" << std::endl;
    std::cout << "Argument #2: " << std::endl;
    std::cout << "\tBlocks per Set " << std::endl;
    std::cout << "Argument #3: " << std::endl;
    std::cout << "\tBlock Size: " << std::endl;
    std::cout << "Argument #4: " << std::endl;
    std::cout << "\tmiss policy: [write-allocate] or N/A" << std::endl;
    std::cout << "Argument #5: " << std::endl;
    std::cout << "\twrite policy: [write-through] or N/A" << std::endl;
    std::cout << "Argument #6:" << std::endl;
    std::cout << "\treplacement algorithm: [lru] [fifo] or N/A" << std::endl;
    std::cout << "Argument #7: " << std::endl;
    std::cout << "\tInput file" << std::endl;
    return 1;  
  } else {
    size_t input_set_amount = (size_t)atoi(argv[1]);
    size_t input_block_amount = (size_t)atoi(argv[2]);
    size_t input_block_size = (size_t)atoi(argv[3]);
    std::string input_miss_policy(argv[4]);
    std::string input_write_policy(argv[5]);
    std::string input_replacement_alg(argv[6]);
    std::ifstream input_file(argv[7]);
    
    std::string input;
    std::string input_instruction;
    std::string input_hex;
    
    DM_Cache myCache = DM_Cache(input_set_amount, input_block_amount,
    input_block_size, CACHE_ACCESS, MEMORY_ACCESS);
    myCache.set_miss_policy(input_miss_policy);
    myCache.set_write_policy(input_write_policy);

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
      }
      counter = (counter + 1) % 3;
    }
    myCache.print_results();
  }
  return 1;
}