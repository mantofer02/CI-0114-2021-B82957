#include "../headers/DM_Cache.h"

DM_Cache::DM_Cache (size_t set_amount, size_t block_amount, 
size_t block_size, size_t cache_access_cycle, size_t memory_access_cycle) {
  
  //float result = log2((float)block_size);
  if (set_amount && block_amount == 1) {
    this->set_amount = set_amount;
    this->block_amount = block_amount;
    this->block_size = block_size;
    this->cpu_cycles = 0;
    this->cache_access_cycle = cache_access_cycle;
    this->memory_access_cycle = memory_access_cycle;
    this->mapping_policy = DIRECT_MAPPING;
    this->store_hits = 0;
    this->store_misses = 0;
    this->load_hits = 0;
    this->load_misses = 0;
    
    this->write_back = 0;
    this->write_through = 0;
    this->write_allocate = 0;
    this->no_write_allocate = 0;

    initialize_cache();
  } else {
    std :: cout << "Error at cache initialization" << std :: endl;
  }
}

void DM_Cache::initialize_cache() {
  CacheLine new_block;
  for (size_t i = 0; i < set_amount; i++) {
    // cache_lines.
    this->cache_lines.push_back(new_block);
  }
}

/// for cache assignation
size_t DM_Cache::get_block_address(unsigned long long memory_address) {
  return (memory_address % block_amount);
}

// for cache assigantion
size_t DM_Cache::get_tag_value(unsigned long long memory_address) {
  size_t lsb = log2(this->set_amount);
  size_t tag_value = memory_address >> lsb;
  return tag_value;
}

void DM_Cache::store(unsigned long long memory_address) {
  size_t memory_block_address = get_block_address(memory_address);
  size_t memory_tag_value = get_tag_value(memory_address);

  if (!cache_lines[memory_block_address].is_initialized()) {
    cache_lines[memory_block_address].initialize();
    store_miss(memory_block_address, memory_tag_value);
  } else {
    if ((size_t)cache_lines[memory_block_address].get_tag() != memory_tag_value) {
      store_miss(memory_block_address, memory_tag_value);
    } else {
      store_hit();
    }
  }
}

void DM_Cache::store_miss(size_t memory_block_address, size_t memory_tag_value) {
  if(this->no_write_allocate) {
    // el no write allocate escribe en memoria principal
    // pero como no hay entonces se va a obviar
  }else {
    cache_lines[memory_block_address].set_tag(memory_tag_value);
  }
  
  this->store_misses++;
  this->cpu_cycles += (this->memory_access_cycle + this->cache_access_cycle);
}

void DM_Cache::store_hit() {
  this->store_hits++;
  if (this->write_through) {
    this->cpu_cycles += this->memory_access_cycle;
  }
  this->cpu_cycles += this->cache_access_cycle;
}

void DM_Cache::load(unsigned long long memory_address) {
  size_t memory_block_address = get_block_address(memory_address);
  size_t memory_tag_value = get_tag_value(memory_address);

  if (!cache_lines[memory_block_address].is_initialized()) {
    cache_lines[memory_block_address].initialize();
    load_miss();
  } else {
    if ((size_t)cache_lines[memory_block_address].get_tag() != memory_tag_value) {
      load_miss();
    } else {
      load_hit();
    }
  } 
}

void DM_Cache::load_miss() {
  this->load_misses++;
  this->cpu_cycles += (this->memory_access_cycle + this->cache_access_cycle);
}

void DM_Cache::load_hit() {
  this->load_hits++;
  this->cpu_cycles += this->cache_access_cycle;
}