#ifndef CACHE_H
#define CACHE_H
#include <math.h>
#include <iostream>
#include <vector>

#define LRU 1
#define FIFO 2

#define DIRECT_MAPPING 1
#define FULLY_ASSOCIATIVE 2

#define UNINITIALIAZED 0
#define INITIALIAZED 1
class Cache {
  protected:
    class CacheLine {
      private:
        size_t block_size;
        // numero de conjunto
        // en mapeo directo es 1 2 3 4 5 6
        // en fully asosiative es el mismo
        size_t set_number;
        size_t tag;
        size_t data;
        size_t offset;
        // para write-back policy
        size_t dirty_bit;

        //flag
        int init;

      public:
        CacheLine() {
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
    // todos los accessos
    size_t cpu_cycles;
    std::vector<CacheLine> cache_lines;
    size_t mapping_policy;

    size_t store_hits;
    size_t store_misses;

    size_t load_hits;
    size_t load_misses;

    // size_t tag_size;
    // size_t index_size;

    //flags
    // hit flags
    size_t write_through;
    size_t write_back;

    // miss flags
    size_t no_write_allocate;
    size_t write_allocate;

    int replacement_alg;

  public:
    // virtual Cache(size_t mapping_policy) = 0;
    virtual void initialize_cache() = 0;
    virtual size_t get_block_address (unsigned long long memory_address) = 0;
    virtual void store (unsigned long long memory_address) = 0;
    virtual void load (unsigned long long memory_address) = 0;
    void print_results() {
      std::cout << "Total Loads: " << this->load_hits + this->load_misses << std::endl;
      std::cout << "Total Stores: " << this->store_hits + this->store_misses << std::endl;
      std::cout << "Load Hits: " << this->load_hits << std::endl;
      std::cout << "Load Misses: " << this->load_misses << std::endl;
      std::cout << "Store Hits: " << this->store_hits << std::endl;
      std::cout << "Store Misses: " << this->store_misses << std::endl;
      std::cout << "Total CPU Cycles: " << this->cpu_cycles << std::endl;
    }
    void set_write_policy(std::string input) {
      if (input == "write-through") {
        this->write_through = 1;
      }
    }

    void set_miss_policy(std::string input) {
      if (input == "no-write-allocate") {
        this->no_write_allocate = 1;
      }
    }

  void set_algorithm(std::string alg) {
    if (alg == "lru") {
      this->replacement_alg = LRU;
    }
    if (alg == "fifo") {
      this->replacement_alg = FIFO;
    }
  }

    // virtual ~Cache() = 0;
};
#endif