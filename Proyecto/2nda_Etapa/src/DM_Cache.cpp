#include "../headers/DM_Cache.h"

DM_Cache :: DM_Cache (size_t set_amount, size_t block_amount, 
size_t block_size, size_t cache_access_cycle, size_t memory_access_cycle) {
  
  float result = log2((float)block_size);
  // if (set_amount == block_amount && (result == int(result))) {
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
  // } else {
    // std :: cout << "Error at cache initialization" << std :: endl;
  // }
  initialize_cache();
}

void DM_Cache :: initialize_cache() {
  CacheBlock new_block;
  for (int i = 0; i < block_amount; i++) {
    // cache_blocks.
    this->cache_blocks.push_back(new_block);
  }
}

/// for cache assignation
size_t DM_Cache :: get_block_address(unsigned long long memory_address) {
  // size_t lsb = log2(block_amount);
  return (memory_address % block_amount);
}

// for cache assigantion
size_t DM_Cache :: get_tag_value(unsigned long long memory_address) {
  size_t lsb = log2(block_amount);
  size_t tag_value = memory_address >> lsb;
  return tag_value;
}

void DM_Cache :: store(unsigned long long memory_address) {
  size_t memory_block_address = get_block_address(memory_address);
  size_t memory_tag_value = get_tag_value(memory_address);

  if (!cache_blocks[memory_block_address].is_initialized()) {
    // store miss
  } else {
    if (cache_blocks[memory_block_address].get_tag() != memory_tag_value) {
      // store miss
    } else {
      //store hit
    }
  }

}