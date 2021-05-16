#include "../headers/DM_Cache.h"

DM_Cache :: DM_Cache (size_t set_amount, size_t block_amount, 
size_t block_size, size_t cache_access_cycle, size_t memory_access_cycle) {
  
  float result = log2((float)block_size);
  if (set_amount == block_amount && (result == int(result))) {
    this->set_amount = set_amount;
    this->block_amount = block_amount;
    this->block_size = block_size;
    this->cache_access_cycle = cache_access_cycle;
    this->memory_access_cycle = memory_access_cycle;
    this->mapping_policy = DIRECT_MAPPING;
    this->store_hits = 0;
    this->store_misses = 0;
    this->load_hits = 0;
    this->load_misses = 0;
  } else {
    std :: cout << "Error at cache initialization" << std :: endl;
  }
}

void DM_Cache :: initialize_cache () {
  for (int i = 0; i < block_amount; i++) {
    CacheBlock* new_block = new CacheBlock();
    cache_blocks.push_back(*new_block);
  }
}


size_t DM_Cache :: assign_block_address (unsigned long long memory_address) {
  size_t lsb = log2(block_amount);
  return (lsb % memory_address);
}