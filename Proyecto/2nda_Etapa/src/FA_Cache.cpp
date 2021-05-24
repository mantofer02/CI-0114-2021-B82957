#include "../headers/FA_Cache.h"

FA_Cache::FA_Cache (size_t set_amount, size_t block_amount, 
size_t block_size, size_t cache_access_cycle, size_t memory_access_cycle) {
  
  //float result = log2((float)block_size);
  if (set_amount == 1 && block_amount) {
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
    this->replacement_alg = 0;
    this->iter = 0;
    this->counter = 0;
    this->lru_array = new int[block_amount];
    initialize_cache();
  } else {
    std :: cout << "Error at cache initialization" << std :: endl;
  }
}

void FA_Cache::initialize_cache() {
  CacheLine new_block;
  for (size_t i = 0; i < set_amount; i++) {
    // cache_lines.
    this->cache_lines.push_back(new_block);
  }
}

/// for cache assignation
size_t FA_Cache::get_block_address(unsigned long long memory_address) {
  return (memory_address % block_amount);
}

// for cache assigantion
size_t FA_Cache::get_tag_value(unsigned long long memory_address) {
  size_t lsb = log2(this->set_amount);
  size_t tag_value = memory_address >> lsb;
  return tag_value;
}

void FA_Cache::store(unsigned long long memory_address) {
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
      if (this->replacement_alg == LRU) {
        lru_array[memory_block_address] = counter++;
        counter+=1;
      }
    }
  }
}

void FA_Cache::store_miss(size_t memory_block_address, size_t memory_tag_value) {
  if(this->no_write_allocate) {
    // el no write allocate escribe en memoria principal
    // pero como no hay entonces se va a obviar
  }else {
    if (replacement_alg == FIFO) {
      cache_lines[this->iter].set_tag(memory_tag_value);
      this->iter = ((iter + 1) % this->block_amount);
    }
    
    if (replacement_alg == LRU) {
      int lru = this->counter;
      int index = 0;
      for (size_t i = 0; i < this->block_amount; i++) {
        if (this->lru_array[i] < lru) {
          lru = this->lru_array[i];
          index = i;
        }
      }
      cache_lines[index].set_tag(memory_tag_value);
    } else {
      cache_lines[memory_block_address].set_tag(memory_tag_value);
    }
  }
  this->store_misses++;
  this->cpu_cycles += (this->memory_access_cycle + this->cache_access_cycle);
}

void FA_Cache::store_hit() {
  this->store_hits++;
  if (this->write_through) {
    this->cpu_cycles += this->memory_access_cycle;
  }
  this->cpu_cycles += this->cache_access_cycle;
}

void FA_Cache::load(unsigned long long memory_address) {
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
      if (this->replacement_alg == LRU) {
        lru_array[memory_block_address] = counter++;
        counter+=1;
      }
    }
  } 
}

void FA_Cache::load_miss() {
  this->load_misses++;
  this->cpu_cycles += (this->memory_access_cycle + this->cache_access_cycle);
}

void FA_Cache::load_hit() {
  this->load_hits++;
  this->cpu_cycles += this->cache_access_cycle;
}