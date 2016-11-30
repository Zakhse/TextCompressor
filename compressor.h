#ifndef TEXTCOMPRESSOR_COMPRESSOR_H
#define TEXTCOMPRESSOR_COMPRESSOR_H

#include <unordered_map>

typedef std::unordered_map<char32_t, uint32_t> Alphabet;
typedef std::pair<char32_t, uint32_t> AlphabetSymbol;
typedef std::unordered_map<char32_t, std::string> CodeMap;
typedef std::unordered_map<std::string, char32_t> CodeMapInversed;

enum compression_algorithm
{
    HUFFMAN, SHANNON_FANO
};

void compress(std::string path_to_file, compression_algorithm algo);

void decompress(std::string path_to_file);

#endif //TEXTCOMPRESSOR_COMPRESSOR_H
