#ifndef FA_CACHE_H
#define FA_CACHE_H
#include "Cache.h"

class FA_Cache : public Cache {
  public:
    FA_Cache(size_t set_amount, size_t block_amount, size_t block_size,
    size_t cache_access_cycle, size_t memory_access_cycle);
    // el override es por seguridad
    void initialize_cache() override;
    size_t get_block_address(unsigned long long memory_address) override;
    size_t get_tag_value(unsigned long long memory_address);
    void store(unsigned long long memory_address) override;
    void store_miss(size_t memory_block_address, size_t memory_tag_value);
    void store_hit();
    void load(unsigned long long memory_address);
    void load_miss();
    void load_hit();
};
#endif