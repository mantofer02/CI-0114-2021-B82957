#ifndef DM_CACHE_H
#define DM_CACHE_H

#include "Cache.h"

class DM_Cache : public Cache {
  public:
    DM_Cache(size_t set_amount, size_t block_amount, size_t block_size,
    size_t cache_access_cycle, size_t memory_access_cycle);
    
    
    // el override es por seguridad
    void initialize_cache() override;
    size_t get_block_address (unsigned long long memory_address) override;
    size_t get_tag_value (unsigned long long memory_address);
    void store (unsigned long long memory_address) override;
};
#endif