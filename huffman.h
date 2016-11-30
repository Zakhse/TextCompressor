#ifndef TEXTCOMPRESSOR_HUFFMAN_H
#define TEXTCOMPRESSOR_HUFFMAN_H

#include "compressor.h"

#include <vector>
#include <map>


CodeMap create_huffman_codes(Alphabet &alphabet);

#endif //TEXTCOMPRESSOR_HUFFMAN_H
