#ifndef TEXTCOMPRESSOR_FOR_DEBUG_H
#define TEXTCOMPRESSOR_FOR_DEBUG_H

#include "huffman.h"
#include "compressor.h"

#define debug 0
#define dbg if(debug)

void test_table(std::string path);

void print_alphabet(Alphabet alphabet);

void print_code_map(CodeMap &codes);

void print_inversed_huffman(CodeMapInversed &codes);

class Counter
{
public:
    static uint64_t counter;

    static void add(int ops);

    static uint64_t get();
};

#endif //TEXTCOMPRESSOR_FOR_DEBUG_H
