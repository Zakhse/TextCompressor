/**
 * Created by Zakharov Sergey (aka Zakhse),
 * Student of NRU HSE, the Faculty of Computer Science, Software Engineering
 *
 * 2k16, November
 */

#include "for_debug.h"

#include <iostream>


void print_alphabet(Alphabet &alphabet)
{
    for (std::pair<char32_t, uint32_t> el :alphabet)
        std::cout << el.first << " " << el.second << "\n";
}

void print_code_map(CodeMap &codes)
{
    for (std::pair<char32_t, std::string> el :codes)
        std::cout << el.first << " " << el.second << "\n";
}

void print_inversed_huffman(CodeMapInversed &codes)
{
    for (std::pair<std::string, char32_t> el :codes)
        std::cout << el.first << " " << el.second << "\n";
}

void test_table(std::string path)
{
    std::string path_wo_extension = path.substr(0, path.size() - 4);
    std::cout << path.substr(path.find_last_of("/") + 1) << ";";

    Counter::counter = 0;
    compress(path_wo_extension + ".txt", compression_algorithm::HUFFMAN);
    std::cout << Counter::get() << ";";

    Counter::counter = 0;
    compress(path_wo_extension + ".txt", compression_algorithm::SHANNON_FANO);
    std::cout << Counter::get() << ";";

    Counter::counter = 0;
    decompress(path_wo_extension + ".huff");
    std::cout << Counter::get() << ";";

    Counter::counter = 0;
    decompress(path_wo_extension + ".shan");
    std::cout << Counter::get() << ";\n";
}

void Counter::add(int ops) { counter += ops; }

uint64_t Counter::get() { return counter; }

uint64_t Counter::counter = 0;
