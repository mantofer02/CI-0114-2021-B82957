---
tags: Arquitectura de Computadores
title: Cache Memory
---
# Cache Memory: Apendice de Información relevante para la memoria cache y su implementaicon
## Estudiante Marco Ferraro
### Computer Memory Overview
![](https://i.imgur.com/9la8l1W.png)
Location:
* Internal memory is often equated with main memory, but there are other forms of internal memory. The processor requires its own local memory, in the form of registers.**Cache is another form of internal memory**
* External memory consists of peripheral storage devices, such as disk and tape, that are accessible to the processor via I/O controllers.
* An obvious characteristic of memory is its capacity. For internal memory, this is typically expressed in terms of bytes (1 byte = 8 bits) or words. Common word lengths are 8, 16, and 32 bits. External memory capacity is typically expressed in terms of bytes.
* **Word:** The “natural” unit of organization of memory. The size of a word is typically equal to the number of bits used to represent an integer
* **Addressable units:** In some systems, the addressable unit is the word. How ever, many systems allow addressing at the byte level
* **Unit of transfer:** For main memory, this is the number of bits read out of or written into memory at a time. For external memory, data are often transferred in much larger units than a word, and these are referred to as blocks.

### Methods of accessing data units
* Sequential access: Memory is organized into units of data, called records. Access must be made in a specific linear sequence. Piense en Tape Units
* Direct Access: As with sequential access, direct access involves a shared. **read–write mechanism.** However, individual blocks or records have a unique address based on physical location. Disk units, discussed in are direct access.
* Random Access: Each addressable location in memory has a unique, physically wiredin addressing mechanism. Thus, any location can be selected at random and directly addressed and accessed. Main Memory and Cache.
* Associative: This is a random access type of memory that enables one to make a comparison of desired bit locations within a word for a specified match, and to do this for all words simultaneously. Cache memories may employ associative access.

### Performance
* Access Time (Latency): For random-access memory the time from the instant that an address is presented to the memory to the instant that data have been stored or made available for use. For ­non-random-access memory, access time is the time it takes to position the read–write mechanism at the desired location.
* Memory Cycle time: This concept is primarily applied to ­random-access memory and consists of the access time plus any additional time required before a second access can commence. **Note that memory cycle time is concerned with the system bus, not the processor**
* Transfer Rate: This is the rate at which data can be transferred into or out of a memory unit. For random-access memory, it is equal to 1/(cycle time)

Faster access time, greater cost per bit

Greater capacity, smaller cost per bit

Greater capacity, slower access time

Flujo de una jerarquia de memoria
1. Decreasing cost per bit
2. Increasing Capacity
3. Increasing Access Time
4. Decreasing frequency of access of the memory by the processor

![](https://i.imgur.com/e6Cli2w.png)

## Cache Memory Principles 4.2
![](https://i.imgur.com/rwoCvie.png)
In referring to the basic unit of the cache, the term line is used, rather than the term block, for two reasons: (1) to avoid confusion with a main memory block, which contains the same number of data words as a cache line; and (2) because a cache line includes not only K words of data, just as a main memory block, but also includes tag and control bits.
![](https://i.imgur.com/3MPNciX.png)
**The length of a line, not including tag and control bits, is the line size.** The line size may be as small as 32 bits, with each “word” being a single byte; in this case the
line size is 4 bytes. The number of lines is less than the number of main memory blocks.
If a word in a block of memory is read, that block is transferred to one of the lines of the cache
![](https://i.imgur.com/jEdBIRn.png)

## Elements of Cache Design 4.3
![](https://i.imgur.com/ITRKmdM.png)

### Cache Addresses
A logical cache, also known as a virtual cache, stores data using virtual addresses.
A physical cache stores data using main memory physical addresses.
![](https://i.imgur.com/Dh2Gza2.png)
### Cache Size
The larger the cache, the larger the num-
ber of gates involved in addressing the cache. The result is that large caches tend
to be slightly slower than small ones

### Mapping Function
#### Direct Mapping
The simplest technique, known as direct mapping, maps each block
of main memory into only one possible cache line.
![](https://i.imgur.com/9wy3OMu.png)
![](https://i.imgur.com/TpD5HH5.png)
The direct mapping technique is simple and inexpensive to implement. Its main disadvantage is that there is a fixed cache location for any given block. Thus, if a program happens to reference words repeatedly from two different blocks that map into the same line, then the blocks will be continually swapped in the cache, and the hit ratio will be low (a phenomenon known as thrashing).

#### Associative Mapping
Associative mapping overcomes the disadvantage of direct mapping by permitting each main memory block to be loaded into any line of the
cache.
In this case, the cache control logic interprets a memory address simply as a Tag and a Word field. **The Tag field uniquely identifies a block of main memory.** To determine whether a block is in the cache, the cache control logic must simultaneously examine every line’s tag for a match.
![](https://i.imgur.com/6kMd2WS.png)
![](https://i.imgur.com/DskVQ6F.png)
![](https://i.imgur.com/er62i27.png)
