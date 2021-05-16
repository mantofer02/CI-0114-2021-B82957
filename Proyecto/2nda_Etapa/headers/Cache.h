#ifndef CACHE_H
#define CACHE_H
#include <math.h>
#include <iostream>
#include <vector>

#define DIRECT_MAPPING 1
#define FULLY_ASSOCIATIVE 2
#define UNINITIALIAZED 0
#define INITIALIAZED 1
class Cache {
  protected:
    class CacheBlock {
      private:
        size_t block_size;
        // numero de conjunto
        // en mapeo directo es 1 2 3 4 5 6
        // en fully asosiative es el mismo
        size_t set_number;
        size_t tag;
        size_t data;
        size_t offset;

        //flag
        int init;

      public:
        CacheBlock() {
          std :: cout << "CONSTRUCTOR" << std :: endl;
          this->block_size = 0;
          this->set_number = 0;
          this->tag = 0;
          this->data = 0;
          this->offset = 0;
          this->init = UNINITIALIAZED;
        }
        
        int is_initialized () {
          if (this->init == INITIALIAZED) {
            return 1;
          } else {
            return 0;
          }
        }

        void initialize () {
          this->init = INITIALIAZED;
        }

        size_t get_block_size() {
          return this->block_size;
        }
        void set_block_size(size_t n) {
          this->block_size = n;
        }
        size_t get_set_number() {
          return this->set_number;
        }
        void set_set_number(size_t n) {
          this->set_number = n;
        }
        int get_tag() {
          return this->tag;
        }
        void set_tag(size_t n) {
          this->tag = n;
        }
    };
    // cuantos conjuntos hay
    size_t set_amount;
    // cuantos bloques hay
    size_t block_amount;
    // si son iguales es mapeo directo
    // si no es n-way associative
    size_t block_size;
    size_t cache_access_cycle;
    size_t memory_access_cycle;

    std::vector<CacheBlock> cache_blocks;
    size_t mapping_policy;

    size_t store_hits;
    size_t store_misses;

    size_t load_hits;
    size_t load_misses;

    // size_t tag_size;
    // size_t index_size;

    //flags
    size_t write_allocate;
    size_t write_through;
    size_t write_back;


  public:

    // virtual Cache(size_t mapping_policy) = 0;
    virtual void initialize_cache() = 0;
    virtual size_t get_block_address (unsigned long long memory_address) = 0;
    virtual void store (unsigned long long memory_address) = 0;
    // virtual ~Cache() = 0;
};


#endif